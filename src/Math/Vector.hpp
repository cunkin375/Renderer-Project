#include <concepts>
#include <cstddef>

namespace Math {

// Numbers are either floating points or integral types
template <typename T>
concept Number = std::floating_point<T> || std::integral<T>;

// Forward Declaration
template <std::size_t N, Number T>
struct Vector;

// 3D Vector of some Number Type
// NOTE: Number is used to declare a template that containsonly Number Types
template<Number T>
struct Vector<3, T> {
    T x{}, y{}, z{};

    // NOTE: constexpr allows for compile-time evaluation of constructors and functions
    constexpr Vector() = default;

    // Scalar copy
    constexpr Vector(T scalar) : x(scalar), y(scalar), z(scalar) {}

    // Vector copy
    constexpr Vector(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    // returns reference to modified vector type
    constexpr Vector& operator+=(const Vector& right) {
        x += right.x; y += right.y; z += right.z;
        return *this; // <- do not change, this prevents undefined behavior
    }

    friend constexpr Vector operator+(Vector left, const Vector& right) { 
        return left += right;
    }

    friend constexpr Vector operator*(Vector vector, T scalar) {
        return Vector(vector.x * scalar, vector.y * scalar, vector.z * scalar);
    }

};

// 2D Vector of some Number Type
template<Number T>
struct Vector<2, T> {
    T x{}, y{}, z{};

    constexpr Vector() = default;
    constexpr Vector(T scalar) : x(scalar), y(scalar), z(scalar) {}
    constexpr Vector(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

};

}
