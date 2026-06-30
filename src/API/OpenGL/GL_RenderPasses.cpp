#include "GL_RenderPasses.hpp"

#include <glad/glad.h>

#include <string_view>

#include "Types/GL_MeshBuffer.hpp"
#include "Types/GL_Shader.hpp"

#include "ResourceHandling/ResourceManager.hpp"
#include "Util/Log.hpp"

// temporary
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace {
using Indices = GLvoid *;
using ModelName = std::string_view;
using ShaderName = std::string_view;
// ShaderName cannot be string_view because GetUniformLocation uses it to interact with OpenGL's C library
using ShaderUniform = std::string;
using ShaderUniformList = std::vector<ShaderUniform>;
} // namespace

namespace OpenGLRenderer {
extern std::vector<OpenGLMeshBuffer> g_meshes;
extern StringMap<OpenGLShader> g_shaders;

void GenericPass(std::string_view model_name, std::string_view shader_name) {
    auto info = ResourceManager::GetGPUModelInfo(model_name);
    if (info.index_count > 0) {
        g_shaders.find(shader_name)->second.Bind();
        g_meshes[info.handle].Bind();
        glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);
        g_meshes[info.handle].Unbind();
    } else {
        Log::Error("GenericPass failed to fetch from GetGPUModelInfo!");
    }
}

void RenderPass() { 
    auto info = ResourceManager::GetGPUModelInfo("triangle");
    static constexpr auto translation = Matrix4{Vector3{0.5f, 0.0f, 0.0f}};
    // static constexpr auto translation = Matrix4{};

    if (info.index_count > 0) {
        auto &shader = g_shaders.find("Test")->second;
        shader.Bind();

        const auto translation_uniform = shader.GetUniformLocation("translation");
        glUniformMatrix4fv(translation_uniform, 1, GL_FALSE, translation.GetView().data());

        g_meshes[info.handle].Bind();

        glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);

        g_meshes[info.handle].Unbind();
    } else {
        Log::Error("GenericPass failed to fetch from GetGPUModelInfo!");
    }
}

void ShaderToyPass() { GenericPass(ModelName{"ShaderToy"}, ShaderName{"ShaderToy"}); }

} // namespace OpenGLRenderer
