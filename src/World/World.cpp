#include "World.hpp"

#include "ResourceHandling/Types/Common.hpp"
#include "World/Camera.hpp"
#include "World/Object.hpp"
#include "World/Scene.hpp"

#include "Renderer/Renderer.hpp"
#include "ResourceHandling/ResourceManager.hpp"

#include "Util/Aliases.hpp"

#include <numbers>

namespace World
{
auto g_scene = Scene{};
auto g_camera = Camera{}; // this will absolutely change

void Init()
{
    auto model_map = ResourceManager::GetModelMap();
    if (auto it = model_map.find("cube"); it != std::ranges::cend(model_map))
    {
        LoadedModelData *model_view = &(it->second);
        g_scene.objects.emplace_back(Object{ model_view });
    }

    g_camera = Camera{
        Vector3{ 0.0f, 0.0f, 3.0f }, // eye
        Vector3{ 0.0f, 0.0f, 3.0f }, // look_at
        Vector3{ 0.0f, 1.0f, 3.0f }, // up
        std::numbers::pi_v<f32> / 2.0f,
        0.001f, // near plane
        100.0f  // far plane
    };

    UpdateSceneContext();
}

void UpdateSceneContext()
{
    // receive something here and pass the new scene to the renderer
    Renderer::UpdateViewportBuffers(g_scene, g_camera);
}
} // namespace World
