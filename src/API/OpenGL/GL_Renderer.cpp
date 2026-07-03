#include "GL_Renderer.hpp"

#include "GL_RenderPasses.hpp"
#include "Types/GL_MeshBuffer.hpp"
#include "Types/GL_SSBO.hpp"
#include "Types/GL_Shader.hpp"

#include "ResourceHandling/ResourceManager.hpp"
#include "Util/Log.hpp"
#include "Util/StringHash.hpp"

namespace OpenGLRenderer {
std::vector<OpenGLMeshBuffer> g_meshes;
StringMap<OpenGLShader> g_shaders;
StringMap<OpenGLSSBO> g_shader_storage_buffer_objects;

void Init() {
    LoadShaders();
    Log::Info("Shaders Loaded!");
}

void Destroy() {
    g_meshes.clear();
    g_shaders.clear();
    g_shader_storage_buffer_objects.clear();
}

void LoadShader(const ShaderName &name, const ShaderPaths &shader_paths, const DefineDirectives &defines) {
    const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, "", defines);
    if (!inserted) {
        Log::Error("Renderer::LoadShader() failed: '{}' already exists\n!", name);
    }
}

void LoadShader(const SubDirectory &sub_directory, const ShaderName &name, const ShaderPaths &shader_paths,
                const DefineDirectives &defines) {
    const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, sub_directory, defines);
    if (!inserted) {
        Log::Error("Renderer::LoadShader() failed: '{}' already exists\n!", name);
    }
}

void LoadShaders() {
    LoadShader(ShaderName{"Test"},
               ShaderPaths{"test_fragment_shader_460.frag", "test_vertex_shader_460.vert"});
    LoadShader(ShaderName{"ShaderToy"}, ShaderPaths{"shader_toy_460.frag", "shader_toy_460.vert"});
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

void UploadVertexData() {
    auto &models = ResourceManager::GetModelMap();
    for (auto &[name, model] : models) {
        if (!model.is_uploaded) {
            g_meshes.emplace_back(ModelData{model.vertices, model.indices}, name);
            model.handle = g_meshes.size() - 1;
            model.is_uploaded = true;
            Log::Info("Uploaded {} to GPU", name);
        }
    }
}

void Render(Viewport viewport) {
    // RenderPass();
    CubePass(viewport);
    // ShaderToyPass();
}
} // namespace OpenGLRenderer
