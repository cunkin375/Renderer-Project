#pragma once

#include <string>
#include <unordered_map>

#include "App/Types.hpp"

using ShaderHandle = i32;
using ProgramHandle = ShaderHandle;
using GLUniformCache = std::unordered_map<std::string, i32>;

struct OpenGLShaderModule {
private:
    ShaderHandle _handle = -1;
    std::string _filename = "";
    std::string _errors = "";
    std::string _final_source = "";

public:
    OpenGLShaderModule(const std::string& filename, 
                       const std::vector<std::string>& defines);
    ShaderHandle GetHandle() const;
    bool CompilationFailed() const;
    std::string& GetFilename() const;
    std::string& GetErrors() const;
    inline const std::string& GetFinalSource() const { return _final_source; }
};

struct OpenGLShader {
private:
    std::vector<std::string> _defines;
    std::vector<std::string> _shader_paths;
    GLUniformCache _uniform_locations;
    ProgramHandle _handle = -1;
    std::string _sub_directory = "";

public:
    OpenGLShader(std::vector<std::string>& shader_paths, 
                 const std::string sub_directory, 
                 const std::vector<std::string>& defines);
    void Bind();
    bool Load(const std::vector<std::string>& shader_paths);
};
