#pragma once

#include "Math/Vector.hpp"
#include "Util/Aliases.hpp"

struct Resolution {
    ivec2 size;
};

struct Vertex {
    vec3 position{};

    Vertex(f32 x, f32 y, f32 z) : position{ vec3{x, y, z} } {}

    Vertex(const vec3& _position) : position{ _position } {}

};
