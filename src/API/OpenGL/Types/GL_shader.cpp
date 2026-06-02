#include "GL_shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <ranges>
#include <unordered_set>
#include <filesystem>
#include <fstream>

// TODO: IMPLEMENT ALL FUNCTIONS IN GL_shader.hpp

struct ShaderParseContext {
    std::unordered_set<std::string> included_paths;
    bool version_inserted = false;
    bool root_version_seen = false;
};

using BriefLog = bool;

/*** === HELPER FUNCTIONS === ***/
namespace {
    std::string GetLinkingErrors(ProgramHandle program, BriefLog brief)
    {
        i32 link_status;
        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (link_status != GL_FALSE) 
        {
            return "";
        }

        i32 log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len < 0)
        {
            return "\n    An unknown linking error occured (no logs available).\n";
        }

        auto log_buffer = std::vector<char>(log_len + 1); // needs null terminator
        glGetProgramInfoLog(program, log_len, NULL, log_buffer.data());

        if (!brief)
        {
            return std::string{ log_buffer.data() };
        }

        std::string line;
        auto log_stream = std::stringstream{ log_buffer.data() };
        const std::string assembly_start_delim = "--- internal assmebly text ---";

        std::string result = "\n";

        while(std::getline(log_stream, line))
        {
            result += "    " + line + "\n";
            if(line.find(assembly_start_delim) != std::string::npos)
            {
                result += "    (Internal assembly text omitted for brevity)";
                break;
            }
        }

        return result;
    }

    std::string LTrimCopy(const std::string& str)
    {
        size_t start = str.find_first_not_of(" \t\r");
        return (start == std::string::npos) ? "" : str.substr(start);
    }

    std::optional<std::string> TryParseInclude(const std::string& line)
    {
        std::string trimmed = LTrimCopy(line);
        if (!trimmed.starts_with("#include"))
        {
            return std::nullopt;
        }
        size_t first_quote = trimmed.find('"');
        if (first_quote == std::string::npos)
        {
            return std::nullopt;
        }
        size_t second_quote = trimmed.find('"', first_quote + 1);
        if (second_quote == std::string::npos)
        {
            return std::nullopt;
        }
        std::string include_file = trimmed.substr(first_quote + 1, second_quote - first_quote - 1);
        return (include_file.empty()) ? std::nullopt : std::make_optional(trimmed);
    }

    void ParseFile(const std::string& filepath,
                std::string& output_string,
                std::vector<std::string>& line_to_file,
                ShaderParseContext& context,
                const std::string& root_filepath) 
    {
        std::string base_dir = std::filesystem::path(filepath).parent_path().string();
        std::string filename = std::filesystem::path(filepath).filename().string();
        std::string line;
        auto file = std::ifstream{ filepath };
        bool first_line_of_file = true;
        i32 file_line_number = 1;

        if (!file.is_open())
        {
            std::cerr << "\n---------------------------------------------------------------\n\n";
            std::cerr << "ERROR: Failed to open shader file: " << filepath << "\n";
            std::cerr << "\n---------------------------------------------------------------\n";
            return;
        }

        while(std::getline(file, line))
        {
            // ignore BOM char
            if (first_line_of_file && line.starts_with("\xEF\xBB\xFF"))
            {
                line.erase(0, 3);
                first_line_of_file = false;
            }

            // handle #include directives
            if(auto include_file = TryParseInclude(line))
            {
                using namespace std::filesystem;
                std::string include_path = std::filesystem::weakly_canonical(path(base_dir) / path(*include_file)).string();

                if (context.included_paths.insert(include_path).second)
                {
                    ParseFile(include_path, output_string, line_to_file, context, root_filepath);
                }

                file_line_number++;
                continue;
            }

            // prevent duplicate version directives
            std::string triimed = LTrimCopy(line);
            if (line.starts_with("#version"))
            {
                if (filepath != root_filepath)
                {
                    std::cout << "\n---------------------------------------------------------------\n\n";
                    std::cout << "SHADER PARSE WARNING: Skipping #version directive in included file: " << filepath << "(line " << file_line_number << ")" << "\n";
                    std::cout << "\n---------------------------------------------------------------\n";
                    file_line_number++;
                    continue;
                }
                context.root_version_seen = true;
            }

            output_string += line + "\n";
            line_to_file.emplace_back(filepath + "(line " + std::to_string(file_line_number) + ")");
        }

        file_line_number++;
    }
}

/*** === UPPER SHADER FUNCTIONS === ***/

OpenGLShader::OpenGLShader(std::vector<std::string>& shader_paths, 
                           const std::string sub_directory, 
                           const std::vector<std::string>& defines)
                          : defines_{ defines }
                          , shader_paths_{ shader_paths }
                          , sub_directory_{ sub_directory }
{
    // sources must be assigned before loading
    Load(shader_paths_);
}

bool OpenGLShader::Load(const std::vector<std::string>& shader_paths)
{
    // compile shader modules
    std::vector<OpenGLShaderModule> modules;
    for (const auto& shader_path : shader_paths)
    {
         std::string full_path = sub_directory_.empty() ? shader_path : sub_directory_ + "/" + shader_path;
         modules.emplace_back(full_path, defines_);
    }


    for (auto& module : modules)
    {
        if (module.CompilationFailed())
        {
            std::cerr << "\n---------------------------------------------------------------\n\n";
            std::cerr << " COMPILATION ERROR: " + module.GetFilename() + "\n\n";
            std::cerr << module.GetErrors() + "\n";
            std::cerr << "\n---------------------------------------------------------------\n";
            glDeleteShader(module.GetHandle());
            return false;
        }
    }

    // link shader modules
    ProgramHandle program_temp = glCreateProgram();
    for (auto& module : modules)
    {
        glAttachShader(program_temp, ShaderHandle{module.GetHandle()});
    }
    glLinkProgram(program_temp);
    std::string linking_errors = GetLinkingErrors(program_temp, BriefLog{true});

    if (linking_errors.length())
    {
        std::cerr << "\n---------------------------------------------------------------\n\n";
        std::cerr << " LINKING ERROR: ";
        for (auto [idx, module] : std::views::enumerate(modules))
        {
            auto split = (idx < modules.size() - 1) ? "/" : "";
            std::cerr << module.GetFilename() << split;
            glDeleteShader(module.GetHandle());
        }
        std::cerr << linking_errors << "\n";
        std::cerr << "\n---------------------------------------------------------------\n";
        return false;
    }

    // cleanup after success
    if (handle_ != -1)
    {
        glDeleteProgram(handle_);
    }
    handle_ = program_temp;
    uniform_locations_.clear();

    for (auto& module : modules)
    {
        glDeleteShader(module.GetHandle());
    }

    // success
    return true;
} // end OpenGLShader::Load

void OpenGLShader::Bind() 
{
    glUseProgram(handle_); }

/*** === SHADER MODULE FUNCTIONS === ***/

OpenGLShaderModule::OpenGLShaderModule(const std::string& shader_path, const std::vector<std::string>& defines)
{
    ShaderParseContext context;
    std::vector<std::string> line_map;
    std::string parsed_shader_source = "";
    const std::string& root_path = "resources/shaders/OpenGL" + shader_path;

    ParseFile(root_path, parsed_shader_source, line_map, context, root_path);

}

