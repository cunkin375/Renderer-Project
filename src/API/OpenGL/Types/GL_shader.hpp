#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "App/Types.hpp"
#include "App/Globals.hpp"

using ShaderHandle = i32;
using ProgramHandle = ShaderHandle;
using GLUniformCache = std::unordered_map<std::string, i32>;

struct OpenGLShaderModule {
private:
    ShaderHandle handle_ = -1;
    std::string filename_ = "";
    std::string errors_ = "";
    std::string final_source_ = "";
    std::vector<std::string> line_map_;

public:
    OpenGLShaderModule(const std::string& filename, 
                       const std::vector<std::string>& defines,
                       const std::string& base_path = OpenGL::Globals::shader_path);

    bool CompilationFailed() const { return errors_.length(); }

    const ShaderHandle GetHandle()      const { return handle_; }
    const std::string& GetFilename()    const { return filename_; }
    const std::string& GetErrors()      const { return errors_; }
    const std::string& GetFinalSource() const { return final_source_; }
};

struct OpenGLShader {
private:
    std::vector<std::string> defines_;
    std::vector<std::string> shader_paths_;
    GLUniformCache uniform_locations_;
    ProgramHandle handle_ = -1;
    std::string sub_directory_ = "";
    std::string base_path_ = "";

public:
    OpenGLShader(const std::vector<std::string>& shader_paths, 
                 const std::string& sub_directory, 
                 const std::vector<std::string>& defines,
                 const std::string& base_path = OpenGL::Globals::shader_path);
    void Bind() const;
    bool Load(const std::vector<std::string>& shader_paths);
};
