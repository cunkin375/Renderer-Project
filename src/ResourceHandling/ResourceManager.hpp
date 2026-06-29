#pragma once

#include <string>
#include <vector>

#include "Types/Common.hpp"
#include "Util/StringHash.hpp"

namespace ResourceManager {

using ModelHandle = u32;

struct GPUModelInfo {
    ModelHandle handle;
    u32 index_count;
};

struct LoadedModelData {
    LoadedModelData() = default;
    LoadedModelData(std::vector<VertexData> _vertices, std::vector<IndexData> _indices)
        : vertices{_vertices}, indices{_indices} {}
    std::vector<VertexData> vertices{};
    std::vector<IndexData> indices{};
    ModelHandle handle{};
    bool is_uploaded{false};
};

ModelData Cube();
ModelData Triangle();
ModelData Square();

void Init();
void LoadResources();

void LoadObjectModel(const std::string &filepath);

StringMap<LoadedModelData> &GetModelMap();
GPUModelInfo GetGPUModelInfo(const std::string &filepath);

} // namespace ResourceManager
