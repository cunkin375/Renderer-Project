#pragma once

#include <span>

#include "Util/Aliases.hpp"
#include "Math/Vector.hpp"

using IndexData = u32;

struct VertexData {
    vec3 position{};
    VertexData(float x, float y, float z) : position{vec3{x, y, z}} {}
    VertexData(const vec3 &_position) : position{_position} {}
};

struct ModelData {
    std::span<const VertexData> vertices{};
    std::span<const u32> indices{};
};
