#include "GL_Renderer.hpp"

#include "GL_RenderPasses.hpp"
#include "Types/GL_MeshBuffer.hpp"
#include "Types/GL_SSBO.hpp"
#include "Types/GL_Shader.hpp"

#include "Util/Log.hpp"
#include "Util/StringHash.hpp"

#include "Renderer/Viewport.hpp"

namespace OpenGLRenderer {
std::vector<OpenGLMeshBuffer> g_meshes;
StringMap<OpenGLShader> g_shaders;
StringMap<OpenGLSSBO> g_ssbos;
Renderer::Viewport g_viewport_context;

void Init() {
    LoadShaders();
    Log::Info("GL Shaders Loaded!");

    CreateSSBOs();
    Log::Info("GL SSBOs Created!");
}

void Destroy() {
    g_meshes.clear();
    g_shaders.clear();
    g_ssbos.clear();
}

void LoadShader(const ShaderName &name, const ShaderPaths &shader_paths, const DefineDirectives &defines) {
    const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, "", defines);
    if (!inserted) { Log::Error("LoadShader() failed: '{}' already exists!", name); }
}

void LoadShader(const SubDirectory &sub_directory, const ShaderName &name, const ShaderPaths &shader_paths,
                const DefineDirectives &defines) {
    const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, sub_directory, defines);
    if (!inserted) { Log::Error("LoadShader() failed: '{}' already exists!", name); }
}

void LoadShaders() {
    LoadShader(ShaderName{"Test"},
               ShaderPaths{"test_fragment_shader_460.frag", "test_vertex_shader_460.vert"});
    LoadShader(ShaderName{"ShaderToy"}, ShaderPaths{"shader_toy_460.frag", "shader_toy_460.vert"});
}

void CreateSSBO(const std::string &name, std::size_t buffer_size, GLbitfield flags) {
    auto [it, inserted] = g_ssbos.try_emplace(name, OpenGLSSBO{buffer_size, flags});
    if (!inserted) { Log::Error("CreateSSBO failed: '{}' already exists!", name); }
}

void CreateSSBOs() {
    [[maybe_unused]] GLbitfield static_flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
    GLbitfield dynamic_flags = GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;

    CreateSSBO("Viewport", sizeof(Renderer::ViewportGPUData), dynamic_flags);
    CreateSSBO("Object Transform", sizeof(Matrix4), dynamic_flags);
}

// ReloadShader recompiles an entire shader program, KEEP THIS LIGHT
void ReloadShaders() {
    ReloadShader("Test");
    ReloadShader("ShaderToy");
}

void ReloadShader(std::string_view shader_name) {
    const auto found = g_shaders.find(shader_name);
    if (found != std::ranges::cend(g_shaders)) {
        auto &[key, shader] = *found;
        shader.HotLoad();
    }
}

void Render() {
    RenderPass();
    // CubePass(viewport);
    // ShaderToyPass();
}
} // namespace OpenGLRenderer
