#pragma once

#include <string>
#include <vector>

using SubDirectory = std::string;
using Name = std::string;
using ShaderPaths = std::vector<std::string>;
// DefineDirectives refer to preprocessor directives that can be injected into shader source code
// this allows for a single shader file to be defined with different behaviors according to
// system specifications, runtime-decided optimizations, etc.
using DefineDirectives = std::vector<std::string>;

namespace OpenGLRenderer {
    void Init();

    void LoadShader(const Name &name, const ShaderPaths &shader_paths,
                    const DefineDirectives &defines);

    void LoadShader(const SubDirectory &sub_directory, const Name &name,
                    const ShaderPaths &shader_paths, const DefineDirectives &defines);

    void LoadShaders();

    void ReloadShader(std::string_view shader_name);

    void ReloadShaders();

    void UploadVertexData();

    void Render();

} // namespace OpenGLRenderer
