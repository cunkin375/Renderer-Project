#include "Backend.hpp"

#include "API/OpenGL/GL_Globals.hpp"
#include "Renderer/Renderer.hpp"

#include "API/OpenGL/GL_Backend.hpp"
#include "API/OpenGL/GL_Renderer.hpp"
#include "Integration/GLFW.hpp"
#include "ResourceHandling/ResourceManager.hpp"
#include "Util/DirectoryWatcher.hpp"

namespace Backend {
    auto g_api = API::UNDEFINED;
    auto g_auto_reload_enabled = bool{false};
    std::unique_ptr<DirectoryWatcher> g_shader_watcher;

    bool Init(API api, WindowMode window_mode) {
        g_api = api;

        if (!GLFW::Init(api, window_mode)) {
            return false;
        }

        if (GetAPI() == API::OPENGL) {
            GLFW::MakeContextCurrent();
            OpenGLBackend::Init();
            OpenGLRenderer::Init();
            g_shader_watcher = std::make_unique<DirectoryWatcher>(
                OpenGL::Globals::shader_path,
                [](const DirectoryWatcher::FileEvent &event) -> void {
                    if (event.action == DirectoryWatcher::FileAction::Modified) {
                        Renderer::ReloadShaders();
                    }
                });
            g_shader_watcher->SetEnabled(false);
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
            if (g_shader_watcher) {
                g_shader_watcher->PollEvents();
            }
        }
    }

    void EndFrame() { GLFW::EndFrame(g_api); }

    void Update() {
        switch (GLFW::Update()) {
        case Events::RELOAD_SHADERS:
            Renderer::ReloadShaders();
            break;
        case Events::ENABLE_AUTO_RELOAD_SHADERS:
            g_auto_reload_enabled = !g_auto_reload_enabled;
            g_shader_watcher->SetEnabled(g_auto_reload_enabled);
            break;
        case Events::NONE:
            break;
        }
    }

    void Destroy() {
        if (GetAPI() == API::OPENGL) {
            OpenGLRenderer::Destroy();
        }
        GLFW::Destroy();
    }

    API GetAPI() { return g_api; }

    WindowHandle GetWindowPointer() { return GLFW::GetWindowPointer(); }
} // namespace Backend
