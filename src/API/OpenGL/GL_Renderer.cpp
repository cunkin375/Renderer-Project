#include "GL_Renderer.hpp"

#include <iostream>

#include "GL_RenderPasses.hpp"
#include "Types/GL_MeshBuffer.hpp"
#include "Types/GL_SSBO.hpp"
#include "Types/GL_Shader.hpp"

#include "ResourceHandling/ResourceManager.hpp"
#include "Util/StringHash.hpp"

namespace OpenGLRenderer {
    std::vector<OpenGLMeshBuffer> g_meshes;
    StringMap<OpenGLShader> g_shaders;
    StringMap<OpenGLSSBO>   g_shader_storage_buffer_objects;

    void Init() {
        LoadShaders();
        std::cout << "Shaders Loaded!\n";
    }

    void LoadShader(const ShaderName &name,
                    const ShaderPaths &shader_paths,
                    const DefineDirectives &defines)
    {
        const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, "", defines);
        if (!inserted) { std::cerr << "Renderer::LoadShader() failed: '" << name << "' already exists\n!"; }
    }

    void LoadShader(const SubDirectory &sub_directory,
                    const ShaderName &name,
                    const ShaderPaths &shader_paths,
                    const DefineDirectives &defines)
    {
        const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, sub_directory, defines);
        if (!inserted) { std::cerr << "Renderer::LoadShader() failed: '" << name << "' already exists\n!"; }
    }

    void LoadShaders() {
        LoadShader(ShaderName{"Test"}, ShaderPaths{"test_fragment_shader_460.frag", "test_vertex_shader_460.vert"});
        LoadShader(ShaderName{"ShaderToy"}, ShaderPaths{"shader_toy_460.frag", "shader_toy_460.vert"});
    }

    void ReloadShaders() {
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
                std::cout << "Uploaded " << name << " to GPU.\n";
            }
        }
    }


    void Render() {
        // RenderPass();
        ShaderToyPass();
    }
} // namespace OpenGLRenderer
