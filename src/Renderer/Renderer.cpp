#include "Renderer.hpp"
#include "API/OpenGL/GL_renderer.hpp"
#include "Backend/Backend.hpp"

namespace Renderer {
    void Render() {
        if (API::OPENGL == Backend::GetAPI()) {
            OpenGLRenderer::Render();
        }
    }

    void Init() {
        if (Backend::GetAPI() == API::OPENGL) {
            OpenGLRenderer::Init();
        }
    }
} // namespace Renderer
