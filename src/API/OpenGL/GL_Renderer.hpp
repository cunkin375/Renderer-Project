#pragma once

#include <string>
#include <vector>

using SubDirectory = std::string;
using ShaderName = std::string;
using ShaderPaths = std::vector<std::string>;
// DefineDirectives refer to preprocessor directives that can be injected into shader source code
// this allows for a single shader file to be defined with different behaviors according to
// system specifications, runtime-decided optimizations, etc.
using DefineDirectives = std::vector<std::string>;

namespace OpenGLRenderer {
void Init();
void Destroy();

void LoadShader(const ShaderName &name, const ShaderPaths &shader_paths,
                const DefineDirectives &defines = {});

void LoadShader(const SubDirectory &sub_directory, const ShaderName &name, const ShaderPaths &shader_paths,
                const DefineDirectives &defines = {});

void LoadShaders();

void CreateSSBO(const std::string &name, std::size_t buffer_size, const void *data);

void CreateSSBOs();

void ReloadShader(std::string_view shader_name);

void ReloadShaders();

void Render();

void UploadVertexData();

void UpdateViewportBuffers(const World::Scene &new_scene_context, const World::Camera &new_camera_context);

} // namespace OpenGLRenderer
