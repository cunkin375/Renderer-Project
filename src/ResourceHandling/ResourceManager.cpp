#include "ResourceManager.hpp"

#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

#include "Math/Vector.hpp"
#include "Types/Common.hpp"
#include "Util/Log.hpp"
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
            auto &[key, cube] = *loaded;
            return {.vertices = cube.vertices, .indices = cube.indices};
        }

        [[maybe_unused]] vec3 positions[]{{0.5f, 0.5f, 0.0f},  {0.5f, -0.5f, 0.0f},  {-0.5f, 0.5f, 0.0f},
                         {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{};

        [[maybe_unused]] vec3 normals[]{};

        [[maybe_unused]] vec2 uvs[]{};

        return {};
    }

    ModelData Triangle() {
        const auto loaded = loaded_model_cache.find("triangle");

        if (loaded != std::ranges::cend(loaded_model_cache)) {
            auto &[key, triangle] = *loaded;
            return {.vertices = triangle.vertices, .indices = triangle.indices};
        }

        vec3 positions[]{{0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 2};

        auto [new_item, inserted] = loaded_model_cache.try_emplace(
            "triangle", LoadedModelData{vertices(positions), std::move(indices)});

        if (!inserted) {
            Log::Error("Failed to insert triangle!");
        }

        return {.vertices = new_item->second.vertices, .indices = new_item->second.indices};
    }

    ModelData Square() {
        const auto loaded = loaded_model_cache.find("square");

        if (loaded != std::ranges::cend(loaded_model_cache)) {
            auto &[key, square] = *loaded;
            return {.vertices = square.vertices, .indices = square.indices};
        }

        vec3 positions[]{
            {0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 3, 1, 2, 3};

        auto [new_item, inserted] = loaded_model_cache.try_emplace(
            "square", LoadedModelData{vertices(positions), std::move(indices)});

        if (!inserted) {
            Log::Error("Failed to insert square!");
        }

        return {.vertices = new_item->second.vertices, .indices = new_item->second.indices};
    }

    ModelData ShaderToy() {
        const auto loaded = loaded_model_cache.find("ShaderToy");

        if (loaded != std::ranges::cend(loaded_model_cache)) {
            auto &[key, square] = *loaded;
            return {.vertices = square.vertices, .indices = square.indices};
        }

        vec3 positions[]{
            {1.0f, 1.0f, 0.0f}, {1.0f, -1.0f, 0.0f}, {-1.0f, -1.0f, 0.0f}, {-1.0f, 1.0f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 3, 1, 2, 3};

        auto [new_item, inserted] = loaded_model_cache.try_emplace(
            "ShaderToy", LoadedModelData{vertices(positions), std::move(indices)});

        if (!inserted) {
            Log::Error("Failed to insert square!");
        }

        return {.vertices = new_item->second.vertices, .indices = new_item->second.indices};
    }

    void Init() { LoadResources(); }

    void LoadHardCoded() {
        // Cube();
        Triangle();
        Square();
        ShaderToy();
    }

    void LoadObjectModel(const std::string &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            Log::Error("Failed to open model: {}", filepath);
            return;
        }

        auto object_vertices = std::vector<VertexData>{};
        auto object_indices = std::vector<IndexData>{};

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

        loaded_model_cache.try_emplace(
            filepath, LoadedModelData{std::move(object_vertices), std::move(object_indices)});
    }

    void LoadResources() {
        Log::Info("Loading Resources...");
        LoadHardCoded();
        // LoadObjectModel("resources/models/square.obj");
        LoadObjectModel("resources/models/triangle.obj");
    }

    StringMap<LoadedModelData> &GetModelMap() { return loaded_model_cache; }

    GPUModelInfo GetGPUModelInfo(const std::string &filepath) {
        const auto loaded = loaded_model_cache.find(filepath);
        if (loaded != std::ranges::cend(loaded_model_cache) && loaded->second.is_uploaded) {
            auto &[key, model] = *loaded;
            return {model.handle, static_cast<u32>(model.indices.size())};
        }
        return {0, 0};
    }

} // namespace ResourceManager
