#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Util/Log.hpp"

int main() {
    auto matrix = Matrix4{};
    Log::Info("Matrix:\n{}", matrix);

    auto matrix2 = Matrix4{
        {1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f}};

    auto matrix3 = Matrix4{
        {1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f}};

    auto vector  = Vector3{1.0f, 2.0f, 3.0f};
    auto vector2 = Vector3{2.0f, 4.0f, 3.0f};

    Log::Info("Negative vector: {}", -vector);
    Log::Info("Vector * Scalar: {}", vector * 2);
    Log::Info("Vector * Vector: {}", vector * vector);
    Log::Info("Vector x Vector: {}", Vector3::CrossProduct(vector ,vector2));
    Log::Info("Vector Normalize: {}", Vector3::Normalize(vector));

    Log::Info("Matrix Multiply:\n{}", matrix2 * matrix3);
}
