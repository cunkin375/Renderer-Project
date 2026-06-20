#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "Define/Types.hpp"

using IndexData = std::uint32_t;

struct ModelData {
    std::span<const VertexData> vertices{};
    std::span<const IndexData> indices{};
};

namespace AssetManager {
    void Init();
    void FindAssetPaths();

    ModelData Cube();
    ModelData Triangle();

    struct LoadedModelData {
        LoadedModelData(std::vector<VertexData> _vertices, std::vector<IndexData> _indices)
            : vertices{_vertices}, indices{_indices} {}
        std::vector<VertexData> vertices{};
        std::vector<IndexData> indices{};
    };

} // namespace AssetManager
