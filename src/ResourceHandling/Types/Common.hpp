#pragma once

#include <span>
#include <vector>

#include "Math/Vector.hpp"
#include "Util/Aliases.hpp"

using IndexData = u32;

struct alignas(16) VertexData {
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

struct LoadedModelData {
    LoadedModelData() = default;
    LoadedModelData(std::vector<VertexData> _vertices, std::vector<IndexData> _indices)
        : vertices{_vertices}, indices{_indices} {}
    std::vector<VertexData> vertices{};
    std::vector<IndexData> indices{};
    i32 handle{-1};
    bool is_uploaded{false};
};


struct TextureData {

};

struct MaterialData {

};

