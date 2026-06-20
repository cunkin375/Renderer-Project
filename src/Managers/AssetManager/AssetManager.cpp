#include "AssetManager.hpp"

#include <iostream>
#include <ranges>
#include <utility>

#include "Math/Vector.hpp"
#include "Util/StringHash.hpp"

namespace {
    // Take in ranges of N data use it to build a vector of VertexData object
    // - Forwards tuples of related position, uvs, etc to the VertexData constructor
    // - Returns populated vector<VertexData> object for ModelData and LoadedModelData
    template <typename... Args> std::vector<VertexData> vertices(Args &&...args) {
        return std::views::zip_transform(
                   []<typename... A>(A &&...a) { return VertexData{std::forward<A>(a)...}; },
                   std::forward<Args>(args)...) |
               std::ranges::to<std::vector>();
    }

} // namespace

namespace AssetManager {
    auto loaded_models = StringMap<LoadedModelData>{};

    ModelData Cube() {
        const auto loaded = loaded_models.find("cube");

        if (loaded != std::ranges::cend(loaded_models)) {
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
        const auto loaded = loaded_models.find("triangle");

        if (loaded != std::ranges::cend(loaded_models)) {
            return {.vertices = loaded->second.vertices, .indices = loaded->second.indices};
        }

        vec3 positions[]{{0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 2};

        auto new_item = loaded_models.emplace(
            "triangle", LoadedModelData{vertices(positions), std::move(indices)});

        // oh my god thank you c++ for being so fucking ugly
        return {.vertices = new_item.first->second.vertices,
                .indices = new_item.first->second.indices};
    }

    ModelData Square() {
        const auto loaded = loaded_models.find("square");

        if (loaded != std::ranges::cend(loaded_models)) {
            return {.vertices = loaded->second.vertices, .indices = loaded->second.indices};
        }

        vec3 positions[]{{0.5f, 0.5f, 0.0f},  {0.5f, -0.5f, 0.0f},  {-0.5f, 0.5f, 0.0f},
                         {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

        auto indices = std::vector<IndexData>{0, 1, 3, 1, 2, 3};

        auto new_item = loaded_models.emplace(
            "square", LoadedModelData{vertices(positions), std::move(indices)});

        // oh my god thank you c++ for being so fucking ugly
        return {.vertices = new_item.first->second.vertices,
                .indices = new_item.first->second.indices};
    }

    void Init() {
        std::cout << "Initializing AssetManager...\n";
        FindAssetPaths();
    }

    void FindAssetPaths() {}

} // namespace AssetManager
