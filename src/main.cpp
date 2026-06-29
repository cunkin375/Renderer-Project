#include "Backend/Backend.hpp"
#include "Renderer/Renderer.hpp"
#include "Util/Enums.hpp"
#include "Util/Log.hpp"

int main() {
    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED)) {
        Log::Error("Backend failed to initialize!");
        std::exit(-1);
    }

    Renderer::Init();

    while (Backend::WindowIsOpen()) {
        Backend::BeginFrame();
        Backend::Update();
        Renderer::Render();
        Backend::EndFrame();
    }

    Backend::Destroy();

    Log::Info("Hello, world!");
}
