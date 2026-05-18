#include "Backend.hpp"

#include <GLFW/glfw3.h>

#include "Integration/GLFW.hpp"
#include "API/OpenGL/GL_backend.hpp"
#include "API/OpenGL/GL_renderer.hpp"

namespace Backend {
    API g_api = API::UNDEFINED;

    bool Init(API api, WindowMode window_mode)
    {
        g_api = api;

        if (!GLFW::Init(api, window_mode))
        {
            return false;
        }

        if (GetAPI() == API::OPENGL)
        {
            OpenGLBackend::Init();
            OpenGLRenderer::Init();
        }

        return true;
    }

    bool WindowIsOpen() 
    { 
        return GLFW::WindowIsOpen(); 
    }

    void BeginFrame()
    {
    }

    void EndFrame()
    {
    }

    

    API GetAPI()
    {
        return g_api; 
    }

    WindowHandle GetWindowPointer()
    {
        return GLFW::GetWindowPointer(); 
    }
}
