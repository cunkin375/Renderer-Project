#include "World/Camera.hpp"
#include "World/Scene.hpp"

namespace OpenGLRenderer
{
void RenderPass(const World::Scene *scene_context, const World::Camera *camera_context);
void CubePass(const World::Scene *scene_context, const World::Camera *camera_context);
void ShaderToyPass();
} // namespace OpenGLRenderer
