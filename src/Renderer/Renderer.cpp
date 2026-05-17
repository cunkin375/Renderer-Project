#include "Backend/Backend.hpp"
#include "Renderer.hpp"
#include "API/OpenGL/GL_renderer.hpp"
#include "App/Enums.hpp"

namespace Renderer {
    void Render()
    {
        if (API::OPENGL == Backend::GetAPI())
        {
            OpenGLRenderer::Render();
        }
    }
}
