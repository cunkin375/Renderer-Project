#include "GL_Shader.hpp"

#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>

#include "Util/StringHash.hpp"

struct ShaderParseContext {
    StringSet included_paths;
    bool version_inserted = false;
    bool root_version_seen = false;
};

using BriefLog = bool;

/*** ==== HELPER FUNCTIONS ============================================================================== ***/
namespace {
    std::optional<std::string> GetLinkingErrors(ProgramHandle program, BriefLog brief) {

        i32 link_status;
        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (link_status != GL_FALSE) {
            return std::nullopt;
        }

        i32 log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len < 0) {
            return "\n    An unknown linking error occured (no logs "
                   "available).\n";
        }

        auto log_buffer = std::vector<char>(log_len + 1); // needs null terminator
        glGetProgramInfoLog(program, log_len, NULL, log_buffer.data());

        if (!brief) {
            return std::string{log_buffer.data()};
        }

        std::string line;
        auto log_stream = std::stringstream{log_buffer.data()};
        const std::string assembly_start_delim =
            "--- internal assmebly text ---";

        std::string result = "\n";

        while (std::getline(log_stream, line)) {
            result += "    " + line + "\n";
            // if this is the delimeter stop
            if (line.find(assembly_start_delim) != std::string::npos) {
                result += "    (Internal assembly text omitted for brevity)";
                break;
            }
        }

        return result;
    }

    std::string LeftTrimCopy(const std::string &str) {
        std::size_t start = str.find_first_not_of(" \t\r");
        return (start == std::string::npos) ? "" : str.substr(start);
    }

    std::optional<std::string> TryParseInclude(const std::string &line) {
        std::string trimmed = LeftTrimCopy(line);
        if (!trimmed.starts_with("#include")) {
            return std::nullopt;
        }

        std::size_t first_quote = trimmed.find('"');
        if (first_quote == std::string::npos) {
            return std::nullopt;
        }

        std::size_t second_quote = trimmed.find('"', first_quote + 1);
        if (second_quote == std::string::npos) {
            return std::nullopt;
        }

        std::string include_file =trimmed.substr(first_quote + 1, second_quote - first_quote - 1);
        return (include_file.empty()) ? std::nullopt : std::make_optional(trimmed);
    }

    bool ParseFile(const std::string &filepath, std::string &output_string,
                   std::vector<std::string> &line_to_file,
                   ShaderParseContext &context,
                   const std::string &root_filepath) 
    {
        std::string base_directory = std::filesystem::path(filepath).parent_path().string();
        std::string filename = std::filesystem::path(filepath).filename().string();
        std::string line;
        auto file = std::ifstream{filepath};
        i32 file_line_number = 1;
        bool first_line_of_file = true;

        if (!file.is_open()) {
            std::cerr << "\n---------------------------------------------------------------\n\n";
            std::cerr << "ERROR: Failed to open shader file: " << filepath << "\n";
            std::cerr << "\n---------------------------------------------------------------\n";
            return false;
        }

        while (std::getline(file, line)) {
            // ignore BOM char
            if (first_line_of_file && line.starts_with("\xEF\xBB\xFF")) {
                line.erase(0, 3);
                first_line_of_file = false;
            }

            // handle #include directives
            if (auto include_file = TryParseInclude(line)) {
                using namespace std::filesystem;
                std::string include_path =
                    std::filesystem::weakly_canonical(path(base_directory) / path(*include_file)).string();

                if (context.included_paths.insert(include_path).second) {
                    if (!ParseFile(include_path, output_string, line_to_file, context, root_filepath)) {
                        return false;
                    }
                }

                file_line_number++;
                continue;
            }

            // prevent duplicate version directives
            std::string trimmed = LeftTrimCopy(line);
            if (line.starts_with("#version")) {
                if (filepath != root_filepath) {
                    std::cout << "\n---------------------------------------------------------------\n\n";
                    std::cout << "SHADER PARSE WARNING: Skipping #version directive in included file: "
                              << filepath << "(line " << file_line_number << ")" << "\n";
                    std::cout << "\n---------------------------------------------------------------\n";
                    file_line_number++;
                    continue;
                }
                context.root_version_seen = true;
            }

            output_string += line + "\n";
            line_to_file.emplace_back(filepath + "(line " + std::to_string(file_line_number) + ")");
            file_line_number++;
        }
        return true;
    }

    void InsertDefines(std::string &source, const std::vector<std::string> &defines) {
        if (defines.empty()) {
            return;
        }

        std::string defines_block = "";

        for (const auto &define : defines) {
            defines_block += "#define " + define + "\n";
        }

        if (source.find("#version") == std::string::npos) { 
            return;
        }

        std::size_t new_line_position = source.find("\n");

        if (new_line_position != std::string::npos) {
            source.insert(new_line_position + 1, defines_block);
        }
    }

    std::string GetShaderCompileErrors(const ShaderHandle shader,
                           const std::string &filename,
                           const std::vector<std::string> &line_map) 
    {
        i32 success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success) {
            return "";
        }

        constexpr i32 info_log_buffer_size = 1024;
        char info_log[info_log_buffer_size];

        glGetShaderInfoLog(shader, info_log_buffer_size, nullptr, info_log);

        return std::string{info_log};
    }

} // namespace

/*** ==== UPPER SHADER FUNCTIONS ======================================================================== ***/

OpenGLShader::OpenGLShader(const std::vector<std::string> &shader_paths,
                           const std::string &sub_directory,
                           const std::vector<std::string> &defines,
                           const std::string &base_path)
                         : defines_{ defines }
                         , shader_paths_{ shader_paths }
                         , sub_directory_{ sub_directory }
                         , base_path_{ base_path }
{
    // sources must be assigned before loading
    Load(shader_paths_);
}

bool OpenGLShader::Load(const std::vector<std::string> &shader_paths) {
    // compile shader modules
    std::vector<OpenGLShaderModule> modules;

    for (const auto &shader_path : shader_paths) {
        std::string full_path = sub_directory_.empty() ? shader_path : sub_directory_ + "/" + shader_path;
        modules.emplace_back(full_path, defines_, base_path_);
    }

    for (auto &module : modules) {
        if (module.CompilationFailed()) {
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
    for (auto &module : modules) {
        glAttachShader(program_temp, ShaderHandle{module.GetHandle()});
    }

    glLinkProgram(program_temp);

    if (auto linking_errors = GetLinkingErrors(program_temp, BriefLog{true})) {
        std::cerr << "\n---------------------------------------------------------------\n\n";
        std::cerr << " LINKING ERROR: ";
        for (auto [idx, module] : std::views::enumerate(modules)) {
            auto split = (idx < modules.size() - 1) ? "/" : "";
            std::cerr << module.GetFilename() << split;
            glDeleteShader(module.GetHandle());
        }
        std::cerr << *linking_errors << "\n";
        std::cerr << "\n---------------------------------------------------------------\n";
        return false;
    }

    // cleanup after success
    if (handle_ != -1) {
        glDeleteProgram(handle_);
    }

    handle_ = program_temp;
    uniform_locations_.clear();

    for (auto &module : modules) {
        glDeleteShader(module.GetHandle());
    }

    // success
    return true;
} // OpenGLShader::Load

void OpenGLShader::Bind() const { glUseProgram(handle_); }

/*** ==== SHADER MODULE FUNCTIONS ======================================================================= ***/

OpenGLShaderModule::OpenGLShaderModule(const std::string &shader_path,
                                       const std::vector<std::string> &defines,
                                       const std::string &base_path) 
{
    ShaderParseContext context;
    std::vector<std::string> line_map;
    std::string parsed_shader_source = "";
    const std::string root_path = base_path + shader_path;

    if (!ParseFile(root_path, parsed_shader_source, line_map, context,
                   root_path)) {
        errors_ = "Failed to open or parse shader file: " + root_path;
        filename_ = shader_path;
        return;
    }

    InsertDefines(parsed_shader_source, defines);

    std::string extension = std::filesystem::path(shader_path).extension().string();

    static const StringMap<i32> shader_type_map = {
        {".vert", GL_VERTEX_SHADER},
        {".frag", GL_FRAGMENT_SHADER},
    };

    i32 shader_type = shader_type_map.contains(extension) ? shader_type_map.at(extension) : GL_NONE;

    handle_ = glCreateShader(shader_type);

    // error checking
    const char *shader_code = parsed_shader_source.c_str();

    glShaderSource(handle_, 1, &shader_code, NULL);
    glCompileShader(handle_);
    errors_ = GetShaderCompileErrors(handle_, shader_path, line_map);
    filename_ = shader_path;

    line_map_ = line_map;

    final_source_ = parsed_shader_source;
}
