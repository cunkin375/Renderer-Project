#pragma once

#include "Renderer/Viewport.hpp"

#include "World/Camera.hpp"
#include "World/Scene.hpp"

#include "Util/Enums.hpp"

namespace Renderer::DataManager {

void UploadVertexData();

void UpdateViewportBuffers(const World::Camera &camera, Renderer::Viewport &viewport);
void ExtractFromScene(World::Scene &scene);

}

