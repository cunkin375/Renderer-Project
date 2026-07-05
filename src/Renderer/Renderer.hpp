#pragma once

#include "World/Camera.hpp"
#include "World/Scene.hpp"

namespace Renderer {
void Render();
void Init();
void ReloadShaders();

void UpdateViewportBuffers(const World::Scene &new_scene_context, const World::Camera &new_camera_context);

} // namespace Renderer
