#include "Backend.hpp"

#include "Integration/GLFW.hpp"
#include "API/OpenGL/GL_backend.hpp"
#include "API/OpenGL/GL_renderer.hpp"

namespace Backend {
    API g_api = API::UNDEFINED;

    bool Init(API api, WindowMode window_mode)
    {
        g_api = api;

        if (GetAPI() == API::OPENGL) {
            OpenGLBackend::Init();
            OpenGLRenderer::Init();
        }

        return true;
    }

    void BeginFrame()
    {

    }

    void EndFrame()
    {

    }

    API GetAPI() { return g_api; }

    bool WindowIsOpen() { return GLFW::WindowIsOpen(); }
}
