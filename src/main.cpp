#include "Backend/Backend.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Renderer/Renderer.hpp"
#include "ResourceHandling/Types/Common.hpp"
#include "Util/Enums.hpp"
#include "Util/Log.hpp"

namespace {
void LogDataInformation();
}

int main() {
    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED)) {
        Log::Fatal("Backend failed to initialize!");
        std::exit(-1);
    }

    while (Backend::WindowIsOpen()) {
        Backend::BeginFrame();
        Backend::Update();
        Renderer::Render();
        Backend::EndFrame();
    }

    Backend::Destroy();

    LogDataInformation();

    Log::Info("Hello, world!");
}

// NOTE: all of this is temporary
namespace {
void LogDataInformation() {
    Log::Info("Size of VertexData: {}", sizeof(VertexData));
    Log::Info("Size of ColorVector<f32>: {}", sizeof(Color));
    Log::Info("Size of Vector3<f32>: {}", sizeof(Vector3));
    Log::Info("Offset of of Color VertexData: {}", offsetof(VertexData, color));

    Log::Info("Size of a Matrix4: {}", sizeof(Matrix4));

    auto matrix = Matrix4{};
    Log::Info("Matrix:\n{}", matrix);

    auto matrix2 = Matrix4{
        {1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f}};

    auto matrix3 = Matrix4{
        {1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f}};

    auto vector = Vector3{1.0f, 2.0f, 3.0f};
    auto vector2 = Vector3{2.0f, 4.0f, 3.0f};

    Log::Info("Negative vector: {}", -vector);
    Log::Info("Vector * Scalar: {}", vector * 2);
    Log::Info("Vector * Vector: {}", vector * vector);
    Log::Info("Vector x Vector: {}", Vector3::CrossProduct(vector, vector2));
    Log::Info("Vector Normalize: {}", Vector3::Normalize(vector));
    Log::Info("Vector Normalize In Place: {}", vector.Normalize());

    Log::Info("Matrix Multiply:\n{}", matrix2 * matrix3);
}
} // namespace
