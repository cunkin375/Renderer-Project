#pragma once

#include <span>

#include "Math/Vector.hpp"
#include "Util/Aliases.hpp"

using IndexData = u32;

struct VertexData {
    Vector3 position{};
    Color color{};

    VertexData(float x, float y, float z) : position{Vector3{x, y, z}} {}
    VertexData(const Vector3 &_position) : position{_position} {}
    VertexData(const Vector3 &_position, const Color &_color) : position{_position}, color{_color} {}
};

struct ModelData {
    std::span<const VertexData> vertices{};
    std::span<const u32> indices{};
};
