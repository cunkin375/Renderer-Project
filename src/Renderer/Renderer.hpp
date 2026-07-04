#pragma once

#include "World/Scene.hpp"

namespace Renderer {
void Render();
void Init();
void UploadVertexData();
void ReloadShaders();

void UpdateSceneContext(const World::Scene &new_scene_context);
} // namespace Renderer
