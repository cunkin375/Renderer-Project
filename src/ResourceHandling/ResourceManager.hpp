#pragma once

#include <string_view>
#include <vector>

#include "Types/Common.hpp"
#include "Util/StringHash.hpp"

namespace ResourceManager {

struct GPUModelInfo {
    i32 handle;
    u32 index_count;
};

ModelData Cube();
ModelData Triangle();
ModelData Square();

void Init();
void LoadResources();

void LoadObjectModel(std::string_view filepath);

StringMap<LoadedModelData> &GetModelMap();
GPUModelInfo GetGPUModelInfo(std::string_view filepath);

} // namespace ResourceManager
