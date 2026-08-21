#include "DataManager.hpp"

#include "Renderer/Viewport.hpp"

#include "API/OpenGL/GL_Renderer.hpp"

#include "World/Camera.hpp"
#include "World/Scene.hpp"

#include "Util/Enums.hpp"
#include "Util/Log.hpp"

#include "Backend/Backend.hpp"

namespace Renderer::DataManager
{

void UploadVertexData()
{
    switch (Backend::GetAPI())
    {
        case API::OPENGL: OpenGLRenderer::UploadVertexData();
        case API::UNDEFINED: Log::Error{ "Unknown API in UploadVertexData!" };
    }
}

void UpdateViewportBuffers(const World::Camera &camera, Renderer::Viewport &viewport) {}

void ExtractFromScene(World::Scene &scene) {}

} // namespace Renderer::DataManager
