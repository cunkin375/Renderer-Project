#include "Debug.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "ResourceHandling/Types/Common.hpp"
#include "Util/Log.hpp"

namespace Debug
{
void LogDataInformation()
{
    Log::Info("Size of VertexData: {}", sizeof(VertexData));
    Log::Info("Size of ColorVector<f32>: {}", sizeof(fColor));
    Log::Info("Size of fVector3<f32>: {}", sizeof(fVector3));
    Log::Info("Offset of of Color VertexData: {}", offsetof(VertexData, color));

    Log::Info("Size of a Matrix4: {}", sizeof(Matrix4));

    auto matrix = Matrix4{};
    Log::Info("Matrix:\n{}", matrix);

    auto matrix2 = Matrix4{ { 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f,
                              2.0f, 3.0f, 4.0f } };

    auto matrix3 = Matrix4{ { 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f,
                              2.0f, 3.0f, 4.0f } };

    auto vector = fVector3{ 1.0f, 2.0f, 3.0f };
    auto vector2 = fVector3{ 2.0f, 4.0f, 3.0f };

    Log::Info("Negative vector: {}", -vector);
    Log::Info("Vector * Scalar: {}", vector * 2);
    Log::Info("Vector * Vector: {}", vector * vector);
    Log::Info("Vector x Vector: {}", fVector3::CrossProduct(vector, vector2));
    Log::Info("Vector Normalize: {}", fVector3::Normalize(vector));
    Log::Info("Vector Normalize In Place: {}", vector.Normalize());

    Log::Info("Matrix Multiply:\n{}", matrix2 * matrix3);
}
} // namespace Debug
