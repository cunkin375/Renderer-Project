#include "GL_RenderPasses.hpp"

#include <glad/glad.h>

#include <numbers>
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
using Eye = Vector3;
using LookAt = Vector3;
using Up = Vector3;
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
    // static constexpr auto translation = Matrix4{};

    if (info.index_count > 0) {
        auto &shader = g_shaders.find("Test")->second;
        shader.Bind();

        static constexpr auto model = Matrix4{Vector3{0.0f, 0.0f, 0.0f}};
        const auto model_uniform = shader.GetUniformLocation("model");
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.GetSpan().data());

        static const auto view =
            Matrix4::LookAt(Eye{0.0f, 0.0f, 5.0f}, LookAt{0.0f, 0.0f, 0.0f}, Up{0.0f, 1.0f, 0.0f});
        const auto view_uniform = shader.GetUniformLocation("view");
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view.GetSpan().data());

        // NOTE: hacky please fix next time you get here
        static const auto projection =
            Matrix4::Perspective(std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.001f, 100.0f);
        const auto projection_uniform = shader.GetUniformLocation("projection");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, projection.GetSpan().data());

        g_meshes[info.handle].Bind();

        glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);

        g_meshes[info.handle].Unbind();
    } else {
        Log::Error("GenericPass failed to fetch from GetGPUModelInfo!");
    }
}

void ShaderToyPass() { GenericPass(ModelName{"ShaderToy"}, ShaderName{"ShaderToy"}); }

} // namespace OpenGLRenderer
