#pragma once

#include "Math/Vector.hpp"

struct Resolution {
    ivec2 size;
};

struct VertexData {
    vec3 position{};

    VertexData(float x, float y, float z) : position{vec3{x, y, z}} {}

    VertexData(const vec3 &_position) : position{_position} {}
};
