#include "GL_shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <ranges>

// TODO: IMPLEMENT ALL FUNCTIONS IN GL_shadper.hpp

/*** === HELPER FUNCTIONS === ***/

static auto GetLinkingErrors(i32 program_id, bool brief = false) -> std::string
{
    i32 link_status;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status != GL_FALSE) 
    {
        return "";
    }

    i32 log_len;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len < 0)
    {
        return "\n    An unknown linking error occured (no logs available).\n";
    }

    auto log_buffer = std::vector<char>(log_len + 1); // needs null terminator
    glGetProgramInfoLog(program_id, log_len, NULL, log_buffer.data());

    if (!brief)
    {
        return std::string{ log_buffer.data() };
    }

    std::string line;
    auto full_log = std::string{ log_buffer.data() };
    auto log_stream = std::stringstream{ full_log };
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

void OpenGLShader::Bind() 
{
    glUseProgram(_handle);
}

OpenGLShader::OpenGLShader(std::vector<std::string>& shader_paths, 
                           const std::string sub_directory, 
                           const std::vector<std::string>& defines)
                          : _defines{ defines }
                          , _shader_paths{ shader_paths }
                          , _sub_directory{ sub_directory }
{
    // sources must be assigned before loading
    Load(_shader_paths);
}

auto OpenGLShader::Load(const std::vector<std::string>& shader_paths) -> bool
{
    // compile shader modules
    std::vector<OpenGLShaderModule> modules;
    for (const auto& shader_path : shader_paths)
    {
         std::string full_path = _sub_directory.empty() ? shader_path : _sub_directory + "/" + shader_path;
         modules.push_back(OpenGLShaderModule(full_path, _defines));
    }


    for (auto& module : modules)
    {
        if (module.CompilationFailed())
        {
            std::cout << "\n---------------------------------------------------------------\n\n";
            std::cout << " COMPILATION ERROR: " + module.GetFilename() + "\n\n";
            std::cout << module.GetErrors() + "\n";
            std::cout << "\n---------------------------------------------------------------\n";
            glDeleteShader(module.GetHandle());
            return false;
        }
    }

    // link
    i32 temp_handle = glCreateProgram();
    for (auto& module : modules)
    {
        glAttachShader(temp_handle, module.GetHandle());
    }
    glLinkProgram(temp_handle);
    auto linking_errors = GetLinkingErrors(temp_handle);

    if (linking_errors.length())
    {
        std::cout << "\n---------------------------------------------------------------\n\n";
        std::cout << " LINKING ERROR: ";
        for (auto [idx, module] : std::views::enumerate(modules))
        {
            auto split = (idx < modules.size() - 1) ? "/" : "";
            std::cout << module.GetFilename() << split;
            glDeleteShader(module.GetHandle());
        }
        std::cout << linking_errors << "\n";
        std::cout << "\n---------------------------------------------------------------\n";
        return false;
    }

    // cleanup
    if (_handle != -1)
    {
        glDeleteProgram(_handle);
    }
    _handle = temp_handle;
    _uniform_locations.clear();

    for (auto& module : modules)
    {
        glDeleteShader(module.GetHandle());
    }

    // success
    return true;
}
