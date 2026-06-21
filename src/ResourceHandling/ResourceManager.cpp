#include "ResourceManager.hpp"

#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

#include "Math/Vector.hpp"
#include "Types/Common.hpp"
#include "Util/StringHash.hpp"

namespace {
    // Take in ranges of N data and use it to build a vector of VertexData objects
    // - Forwards tuples of related position, uvs, etc to the VertexData constructor
    // - Returns populated vector<VertexData> object for ModelData and LoadedModelData
    template <typename... Args> std::vector<VertexData> vertices(Args &&...args) {
        return std::views::zip_transform(
                   []<typename... A>(A &&...a) { return VertexData{std::forward<A>(a)...}; },
                   std::forward<Args>(args)...) |
               std::ranges::to<std::vector>();
    }

} // namespace

namespace ResourceManager {
    auto loaded_model_cache = StringMap<LoadedModelData>{};

    ModelData Cube() {
        const auto loaded = loaded_model_cache.find("cube");

        if (loaded != std::ranges::cend(loaded_model_cache)) {
            return {.vertices = loaded->second.vertices, .indices = loaded->second.indices};
        }

        vec3 positions[]{{0.5f, 0.5f, 0.0f},  {0.5f, -0.5f, 0.0f},  {-0.5f, 0.5f, 0.0f},
                         {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{};

        vec3 normals[]{};

        vec2 uvs[] = {};

        return {};
    }

    ModelData Triangle() {
        const auto loaded = loaded_model_cache.find("triangle");

        if (loaded != std::ranges::cend(loaded_model_cache)) {
            return {.vertices = loaded->second.vertices, .indices = loaded->second.indices};
        }

        vec3 positions[]{{0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 2};

        auto new_item = loaded_model_cache.emplace(
            "triangle", LoadedModelData{vertices(positions), std::move(indices)});

        return {.vertices = new_item.first->second.vertices,
                .indices = new_item.first->second.indices};
    }

    ModelData Square() {
        const auto loaded = loaded_model_cache.find("square");

        if (loaded != std::ranges::cend(loaded_model_cache)) {
            return {.vertices = loaded->second.vertices, .indices = loaded->second.indices};
        }

        vec3 positions[]{{0.5f, 0.5f, 0.0f},  {0.5f, -0.5f, 0.0f},  {-0.5f, 0.5f, 0.0f},
                         {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 3, 1, 2, 3};

        auto new_item = loaded_model_cache.emplace(
            "square", LoadedModelData{vertices(positions), std::move(indices)});

        return {.vertices = new_item.first->second.vertices,
                .indices = new_item.first->second.indices};
    }

    void Init() { LoadResources(); }

    void LoadObjectModel(const std::string &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open model: " << filepath << "\n";
            return;
        }

        std::vector<VertexData> object_vertices;
        std::vector<IndexData> object_indices;

        std::string line;
        while (std::getline(file, line)) {
            auto iss = std::istringstream{line};
            auto type = std::string{};
            iss >> type;
            if (type == "v") {
                float x, y, z;
                iss >> x >> y >> z;
                object_vertices.emplace_back(x, y, z);
            } else if (type == "f") {
                u32 i1, i2, i3;
                iss >> i1 >> i2 >> i3;
                object_indices.push_back(i1 - 1);
                object_indices.push_back(i2 - 1);
                object_indices.push_back(i3 - 1);
            }
        }

        loaded_model_cache.emplace(
            filepath, LoadedModelData{vertices(object_vertices), std::move(object_indices)});
    }

    void LoadResources() {
        std::cout << "Loading resources...\n";
        LoadObjectModel("resources/models/square.obj");
        LoadObjectModel("resources/models/triangle.obj");
    }

    StringMap<LoadedModelData> &GetModelMap() { return loaded_model_cache; }

    std::optional<GPUModelInfo> GetGPUModelInfo(const std::string &filepath) {
        const auto it = loaded_model_cache.find(filepath);
        if (it != loaded_model_cache.end() && it->second.is_uploaded) {
            return {{it->second.handle, static_cast<u32>(it->second.indices.size())}};
        }
        return std::nullopt;
    }

} // namespace ResourceManager
