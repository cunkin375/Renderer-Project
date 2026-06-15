#pragma once
#include <concepts>
#include <array>
#include <utility>

/** Linear Algebra Library made to experiment with template metaprogramming */
// NOTE: <linalg> does a lot of this for you (See https://en.cppreference.com/cpp/numeric/linalg)

namespace Math {

// Numbers are either floating points or integral types
template <typename T>
concept Number = std::floating_point<T> || std::integral<T>;

/**
 * Base operations for any vector type using Curiously Recurring Template Pattern (CRTP)
 */
template <typename Derived, Number T, std::size_t N>
struct VectorOperations {
    /* vector += vector using the [] operator of the derived class */
    constexpr Derived& operator+=(const Derived& other) {
        auto& self = static_cast<Derived&>(*this);
        auto add_vector = [&]<std::size_t... Is>(std::index_sequence<Is...>) {
            ((self[Is] += other[Is]), ...);
        };
        add_vector(std::make_index_sequence<N>{});
        return self;
    }

    /* vector *= vector */
    constexpr Derived& operator*=(const Derived& other) {
        auto& self = static_cast<Derived&>(*this);
        auto add_vector = [&]<std::size_t... Is>(std::index_sequence<Is...>) {
            ((self[Is] *= other[Is]), ...);
        };
        add_vector(std::make_index_sequence<N>{});
        return self;
    }

    /* vector += scalar */
    constexpr Derived& operator+=(T scalar) {
        auto& self = static_cast<Derived&>(*this);
        auto add_vector = [&]<std::size_t... Is>(std::index_sequence<Is...>) {
            ((self[Is] += scalar), ...);
        };
        add_vector(std::make_index_sequence<N>{});
        return self;
    }

    /* vector *= scalar */
    constexpr Derived& operator*=(T scalar) {
        auto& self = static_cast<Derived&>(*this);
        auto multiply_scalar = [&]<std::size_t... Is>(std::index_sequence<Is...>) {
            ((self[Is] *= scalar), ...);
        };
        multiply_scalar(std::make_index_sequence<N>{});
        return self;
    }

    // Binary operators (Hidden friends)
    /* vector + vector */
    friend constexpr Derived operator+(Derived left_vector, const Derived& right_vector) {
        left_vector += right_vector;
        return left_vector;
    }

    /* vector * vector */
    friend constexpr Derived operator*(Derived left_vector, const Derived& right_vector) {
        left_vector *= right_vector;
        return left_vector;
    }

    /* vector + scalar */
    friend constexpr Derived operator+(Derived left_vector, T scalar) {
        left_vector += scalar;
        return left_vector;
    }
    
    /* scalar + vector */
    friend constexpr Derived operator+(T scalar, Derived right_vector) {
        right_vector += scalar;
        return right_vector;
    }

    /* vector * scalar */
    friend constexpr Derived operator*(Derived left_vector, T scalar) {
        left_vector *= scalar;
        return left_vector;
    }
    
    /* scalar * vector */
    friend constexpr Derived operator*(T scalar, Derived right_vector) {
        right_vector *= scalar;
        return right_vector;
    }
};

// Primary template for arbitrary N
template <Number T, std::size_t N>
struct Vector : public VectorOperations<Vector<T, N>, T, N> {
    std::array<T, N> data{};

    constexpr Vector() = default;

    constexpr Vector(T scalar) {
        data.fill(scalar);
    }

    template<typename Self>
    constexpr auto&& operator[](this Self&& self, std::size_t i) {
        return std::forward_like<Self>(self).data[i];
    }
};

/*** Specialization for N = 2 ***/
// putting "using Vector2 = Vector<T, 2zu>" near "template<Number T>" makes the compiler fucking scream and try to kill you, DO NOT DO IT!!!!
template<Number T>
struct Vector<T, 2zu> : public VectorOperations<Vector<T, 2zu>, T, 2zu> {
    T x{}, y{};

    constexpr Vector() = default;
    constexpr Vector(T _x, T _y) : x{ _x }, y{ _y } {}
    constexpr Vector(T scalar) : x{ scalar }, y{ scalar } {}

    template<typename Self>
    constexpr auto&& operator[](this Self&& self, std::size_t i) {
        if (i == 0) return std::forward_like<Self>(self).x;
        return std::forward_like<Self>(self).y;
    }
};

/*** Specialization for N = 3 ***/
// - See using Vector2 comment above
template<Number T>
struct Vector<T, 3zu> : public VectorOperations<Vector<T, 3zu>, T, 3zu> {
    T x{}, y{}, z{};

    constexpr Vector() = default;
    constexpr Vector(T _x, T _y, T _z) : x{ _x }, y{ _y }, z{ _z } {}
    constexpr Vector(T scalar) : x{ scalar }, y{ scalar }, z{ scalar } {}

    template<typename Self>
    constexpr auto&& operator[](this Self&& self, std::size_t i) {
        if (i == 0) return std::forward_like<Self>(self).x;
        if (i == 1) return std::forward_like<Self>(self).y;
        return std::forward_like<Self>(self).z;
    }

    using Vector3 = Vector<T, 3zu>; // this is ok, allegedly
    constexpr Vector3 CrossProduct(Vector3 other) {
        auto& self = static_cast<Vector3&>(*this);
        auto x_param = self.y * other.z - self.z * other.y;
        auto y_param = self.z * other.x - self.x * other.z;
        auto z_param = self.x * other.y - self.y * other.x;
        return Vector3{ x_param, y_param, z_param };
    }
};

// Type aliases using the specialization directly
// This is needed for the defined aliases in Types.hpp
template <Number T> using Vector2D = Vector<T, 2zu>;
template <Number T> using Vector3D = Vector<T, 3zu>;

} // namespace Math
