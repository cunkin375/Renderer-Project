#pragma once

#include <string>
#include <unordered_map>

#include "App/Types.hpp"

struct OpenGLShaderModule {
private:
    i32 _handle = -1;
    std::string _filename = "";
    std::string _errors = "";
    std::string _final_source = "";

public:
    OpenGLShaderModule(const std::string& filename, 
                       const std::vector<std::string>& defines);
    i32 GetHandle() const;
    bool CompilationFailed() const;
    std::string& GetFilename() const;
    std::string& GetErrors() const;
    inline const std::string& GetFinalSource() const { return _final_source; }
};

struct OpenGLShader {
private:
    std::vector<std::string> _defines;
    std::vector<std::string> _shader_paths;
    std::unordered_map<std::string, i32> _uniform_locations;
    i32 _handle = -1;
    std::string _sub_directory = "";

public:
    OpenGLShader(std::vector<std::string>& shader_paths, 
                 const std::string sub_directory, 
                 const std::vector<std::string>& defines);
    void Bind();
    bool Load(const std::vector<std::string>& shader_paths);
};
