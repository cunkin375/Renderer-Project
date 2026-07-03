// kill these things please
#include "Renderer/Viewport.hpp"
#include "World/Scene.hpp"

namespace OpenGLRenderer {
void RenderPass(const Renderer::Viewport &viewport, const World::Scene &scene);
void ShaderToyPass();
void CubePass(const Renderer::Viewport &viewport);
} // namespace OpenGLRenderer
