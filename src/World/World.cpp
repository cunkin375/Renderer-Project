#include "World.hpp"

#include "ResourceHandling/Types/Common.hpp"
#include "World/Camera.hpp"
#include "World/Object.hpp"
#include "World/Scene.hpp"

#include "Renderer/Renderer.hpp"
#include "ResourceHandling/ResourceManager.hpp"

namespace World {
auto g_scene = Scene{};
auto g_camera = Camera{}; // this will absolutely change

void Init() {
    auto model_map = ResourceManager::GetModelMap();
    if (auto it = model_map.find("cube"); it != std::ranges::cend(model_map)) {
        LoadedModelData *model_view = &(it->second);
        g_scene.objects.emplace_back(Object{model_view});
    }

    g_camera = Camera{};

    UpdateSceneContext();
}

void UpdateSceneContext() {
    // receive something here and pass the new scene to the renderer
    Renderer::UpdateSceneContext(g_scene);
}
} // namespace World
