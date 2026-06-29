#include "Backend/Backend.hpp"
#include "Math/Vector.hpp"
#include "Renderer/Renderer.hpp"
#include "ResourceHandling/Types/Common.hpp"
#include "Util/Enums.hpp"
#include "Util/Log.hpp"

int main() {
    Log::Info("Size of VertexData: {}", sizeof(VertexData));
    Log::Info("Size of ColorVector<f32>: {}", sizeof(Color));
    Log::Info("Size of Vector3<f32>: {}", sizeof(Vector3));

    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED)) {
        Log::Fatal("Backend failed to initialize!");
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
