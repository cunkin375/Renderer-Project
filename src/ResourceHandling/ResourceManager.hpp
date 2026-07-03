#pragma once

#include <string_view>
#include <vector>

#include "Types/Common.hpp"
#include "Util/StringHash.hpp"

namespace ResourceManager {

using ModelHandle = u32;

struct GPUModelInfo {
    u32 handle;
    u32 index_count;
};

struct LoadedModelData {
    LoadedModelData() = default;
    LoadedModelData(std::vector<VertexData> _vertices, std::vector<IndexData> _indices)
        : vertices{_vertices}, indices{_indices} {}
    std::vector<VertexData> vertices{};
    std::vector<IndexData> indices{};
};

ModelData Cube();
ModelData Triangle();
ModelData Square();

void Init();
void LoadResources();

void LoadObjectModel(std::string_view filepath);

StringMap<LoadedModelData> &GetModelMap();

} // namespace ResourceManager
