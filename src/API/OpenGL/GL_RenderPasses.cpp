#include "GL_RenderPasses.hpp"

#include <glad/glad.h>

#include <string_view>

#include "Types/GL_MeshBuffer.hpp"
#include "Types/GL_Shader.hpp"

#include "Util/Log.hpp"

#include "Renderer/Viewport.hpp"
#include "ResourceHandling/ResourceManager.hpp"
#include "World/Scene.hpp"
#include "World/Camera.hpp"

namespace
{
using Indices = GLvoid *;
using ModelName = std::string_view;
using ShaderName = std::string_view;
// ShaderUniform cannot be string_view because GetUniformLocation uses it to interact with OpenGL's C library
using ShaderUniform = std::string;
using ShaderUniformList = std::vector<ShaderUniform>;
using Eye = fVector3;
using LookAt = fVector3;
using Up = fVector3;
} // namespace

namespace OpenGLRenderer
{
extern std::vector<OpenGLMeshBuffer> g_meshes;
extern StringMap<OpenGLShader> g_shaders;
extern Renderer::Viewport g_viewport_context;
extern const World::Scene *g_scene_context;
extern const World::Camera *g_camera_context;

void GenericPass(std::string_view model_name, std::string_view shader_name) {}

void RenderPass()
{
    auto &shader = g_shaders.find("Test")->second;
    shader.Bind();

    for (const auto &object : g_scene_context->objects)
    {
        auto model_info = object.GetModel();
        if (!model_info || model_info->handle < 0)
        {
            Log::Error("Failed to fetch model info from object!");
            continue;
        }

        // static constexpr auto model = Matrix4{Vector3{0.0f, 0.0f, 0.0f}};
        // const auto model_uniform = shader.GetUniformLocation("model");
        // glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.GetSpan().data());

        const auto view_uniform = shader.GetUniformLocation("view");
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, g_camera_context->View().data());

        // static const auto projection =
        //     Matrix4::Perspective(std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.001f, 100.0f);
        const auto projection_uniform = shader.GetUniformLocation("projection");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE,
                           g_camera_context->Projection(800.0f / 600.0f).data());

        g_meshes[model_info->handle].Bind();

        glDrawElements(GL_TRIANGLES, model_info->indices.size(), GL_UNSIGNED_INT, nullptr);

        g_meshes[model_info->handle].Unbind();
    }
}

void CubePass()
{
    auto info = ResourceManager::GetGPUModelInfo("cube");
    if (info.index_count > 0)
    {
        auto &shader = g_shaders.find("Test")->second;
        shader.Bind();

        // static auto x = 2.0f;
        // static auto y = 0.0f;
        // static auto z = 0.0f;
        // static auto t = 0.0f;
        //
        // x = std::sin(t) * 2.0f;
        // z = std::cos(t) * 2.0f;
        // y = std::sin(t) * 2.0f;
        //
        // t += 0.02f;

        static constexpr auto model = Matrix4{ fVector3{ 0.0f, 0.0f, 0.0f } };
        const auto model_uniform = shader.GetUniformLocation("model");
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.GetSpan().data());

        // const auto view = Matrix4::LookAt(Eye{x, y, z}, LookAt{0.0f, 0.0f, 0.0f}, Up{0.0f, 1.0f, 0.0f});
        const auto view_uniform = shader.GetUniformLocation("view");
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, g_camera_context->View().data());

        // static const auto projection =
        //     Matrix4::Perspective(std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.001f, 100.0f);
        const auto projection_uniform = shader.GetUniformLocation("projection");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE,
                           g_camera_context->Projection(800.0f / 600.0f).data());

        g_meshes[info.handle].Bind();

        glDrawElements(GL_TRIANGLES, info.index_count, GL_UNSIGNED_INT, nullptr);

        g_meshes[info.handle].Unbind();
    }
    else
    {
        Log::Error("CubePass failed to fetch from GetGPUModelInfo!");
    }
}

void ShaderToyPass() { GenericPass(ModelName{ "ShaderToy" }, ShaderName{ "ShaderToy" }); }

} // namespace OpenGLRenderer
