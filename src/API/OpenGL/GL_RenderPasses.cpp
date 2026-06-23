#include "GL_RenderPasses.hpp"

#include <glad/glad.h>
#include <iostream>

#include "Types/GL_MeshBuffer.hpp"
#include "Types/GL_Shader.hpp"
#include "ResourceHandling/ResourceManager.hpp"

namespace {
    using Indices = GLvoid *;
    using ModelName = std::string;
    using ShaderName = std::string;
}

namespace OpenGLRenderer {
    extern std::vector<OpenGLMeshBuffer> g_meshes;
    extern StringMap<OpenGLShader> g_shaders;

    void GenericPass(const std::string& model_name, const std::string& shader_name) {
        auto info = ResourceManager::GetGPUModelInfo(model_name);
        if (info.index_count > 0) {
            g_shaders.find(shader_name)->second.Bind();
            g_meshes[info.handle].Bind();
            glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);
        } else {
            std::cerr << "ERROR::OpenGLRenderer::RenderPass failed to fetch from GetGPUModelInfo!\n";
        }
    }

    void RenderPass() {
        GenericPass(ModelName{"square"}, ShaderName{"Test"});
        // auto info = ResourceManager::GetGPUModelInfo("square");
        // if (info.index_count > 0) {
        //     g_shaders.find("Test")->second.Bind();
        //     g_meshes[info.handle].Bind();
        //     glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);
        // } else {
        //     std::cerr << "ERROR::OpenGLRenderer::RenderPass failed to fetch from GetGPUModelInfo!\n";
        // }
    }

    void ShaderToyPass() {
        GenericPass(ModelName{"ShaderToy"}, ShaderName{"ShaderToy"});
        // auto info = ResourceManager::GetGPUModelInfo("ShaderToy");
        // if (info.index_count > 0) {
        //     g_shaders.find("ShaderToy")->second.Bind();
        //     g_meshes[info.handle].Bind();
        //     glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);
        // }
    }

} // namespace OpenGLRenderer

