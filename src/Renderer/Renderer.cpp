#include "Renderer.hpp"

#include "API/OpenGL/GL_Renderer.hpp"
#include "Backend/Backend.hpp"
#include "Viewport.hpp"
#include "World/Scene.hpp"

namespace Renderer {
auto g_viewport = Viewport{};
auto g_scene = World::Scene{};

void Render() {
    if (API::OPENGL == Backend::GetAPI()) {
        // TODO: THIS IS TEMPORARY AND ONLY MEANT TO PROTOTYPE, VIEWPORT INFORMATION SHOULD BE STORED AND USED
        // IN AN SSBO
        OpenGLRenderer::Render(g_viewport, g_scene);
    }
}

void Init() {
    UploadVertexData();
    g_viewport = Viewport{World::Camera{Vector3{0.0f, 0.0f, 3.0f}, Vector3{0.0f, 0.0f, 0.0f},
                                        Vector3{0.0f, 1.0f, 0.0f}, 45.0f, 800.0f, 600.0f, 0.0001f, 100.0f}};
}

void UploadVertexData() {
    if (Backend::GetAPI() == API::OPENGL) { OpenGLRenderer::UploadVertexData(); }
}

void ReloadShaders() {
    if (API::OPENGL == Backend::GetAPI()) { OpenGLRenderer::ReloadShaders(); }
}

} // namespace Renderer
