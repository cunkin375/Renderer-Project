#pragma once

#include "Math/Vector.hpp"

#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;

using u32 = std::uint32_t;
using u64 = std::uint64_t;

// Should never happen but kept incase of stupid edits / end of the world
static_assert(sizeof(float)  == 4, "App/Types.hpp requires floats to be 4 bytes (32 bits)!!!");
static_assert(sizeof(double) == 8, "App/Types.hpp requires doubles to be 8 bytes (64 bites)!!!");

using f32 = float;
using f64 = double;

using ivec2 = Math::Vector2<i32>;
using ivec3 = Math::Vector3<i32>;

using vec2  = Math::Vector2<f32>;
using vec3  = Math::Vector3<f32>;

struct Resolution {
    ivec2 size;
};

struct Vertex {

};
