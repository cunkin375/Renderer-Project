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

namespace ShaderWatcher {
    void Init(const std::filesystem::path &path) {
        g_shader_watcher =
            std::make_unique<DirectoryWatcher>(path, [](const DirectoryWatcher::FileEvent &event) -> void {
                // this is fired on every event because vim never produces IN_MODIFY
                // it should fire on every event, as an event is only meant to fire when a shader is
                // modified
                // NOTE: DirectoryWatcher might change, so come back here when that happens
                Renderer::ReloadShaders();
            });
        g_shader_watcher->SetEnabled(false);
    }
} // namespace ShaderWatcher

bool Init(API api, WindowMode window_mode) {
    g_api = api;

    if (!GLFW::Init(api, window_mode)) { return false; }

    if (GetAPI() == API::OPENGL) {
        GLFW::MakeContextCurrent();
        OpenGLBackend::Init();
        OpenGLRenderer::Init();
        ShaderWatcher::Init(OpenGL::Globals::shader_path);
    }

    // order of these matters
    ResourceManager::Init();
    Renderer::Init();

    GLFW::ShowWindow(GetWindowPointer().asGLFW());

    return true;
}

bool WindowIsOpen() { return GLFW::WindowIsOpen(); }

void BeginFrame() {
    GLFW::BeginFrame(g_api);
    if (GetAPI() == API::OPENGL) {
        OpenGLBackend::BeginFrame();
        if (g_shader_watcher->IsEnabled()) { g_shader_watcher->PollEvents(); }
    }
}

void EndFrame() { GLFW::EndFrame(g_api); }

void Update() {
    // clang-format off
    switch (GLFW::Update()) {
        case Events::RELOAD_SHADERS: Renderer::ReloadShaders(); break;
        case Events::ENABLE_AUTO_RELOAD_SHADERS:
            g_auto_reload_enabled = !g_auto_reload_enabled;
            g_shader_watcher->SetEnabled(g_auto_reload_enabled);
            break;
        case Events::NONE: break;
    }
    // clang-format on


}

void Destroy() {
    if (GetAPI() == API::OPENGL) { OpenGLRenderer::Destroy(); }
    GLFW::Destroy();
}

API GetAPI() { return g_api; }

WindowHandle GetWindowPointer() { return GLFW::GetWindowPointer(); }

} // namespace Backend
