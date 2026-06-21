#include "Backend.hpp"

#include "API/OpenGL/GL_Backend.hpp"
#include "API/OpenGL/GL_Renderer.hpp"
#include "ResourceHandling/ResourceManager.hpp"
#include "Integration/GLFW.hpp"

namespace Backend {
    API g_api = API::UNDEFINED;

    bool Init(API api, WindowMode window_mode) {
        g_api = api;

        if (!GLFW::Init(api, window_mode)) {
            return false;
        }

        if (GetAPI() == API::OPENGL) {
            GLFW::MakeContextCurrent();
            OpenGLBackend::Init();
            OpenGLRenderer::Init();
        }

        ResourceManager::Init();

        GLFW::ShowWindow(GetWindowPointer().asGLFW());

        return true;
    }

    bool WindowIsOpen() { return GLFW::WindowIsOpen(); }

    void BeginFrame() {
        GLFW::BeginFrame(g_api);
        if (GetAPI() == API::OPENGL) {
            OpenGLBackend::BeginFrame();
        }
    }

    void EndFrame() { GLFW::EndFrame(g_api); }

    void Update() { GLFW::Update(); }

    void Destroy() { GLFW::Destroy(); }

    API GetAPI() { return g_api; }

    WindowHandle GetWindowPointer() { return GLFW::GetWindowPointer(); }
} // namespace Backend
