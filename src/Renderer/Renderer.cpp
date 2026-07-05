#include "Renderer.hpp"

#include "Renderer/DataManager.hpp"

#include "API/OpenGL/GL_Renderer.hpp"

#include "Backend/Backend.hpp"
#include "World/Scene.hpp"


namespace Renderer {

void Render() {
    if (API::OPENGL == Backend::GetAPI()) {
        // TODO: THIS IS TEMPORARY AND ONLY MEANT TO PROTOTYPE, VIEWPORT INFORMATION SHOULD BE STORED AND USED
        // IN AN SSBO
        OpenGLRenderer::Render();
    }
}

void Init() { 
    DataManager::UploadVertexData(); 
}

void UploadVertexData() {
    if (Backend::GetAPI() == API::OPENGL) {}
}

void ReloadShaders() {
    if (API::OPENGL == Backend::GetAPI()) { OpenGLRenderer::ReloadShaders(); }
}

void UpdateViewportBuffers(const World::Scene &new_scene_context, const World::Camera &new_camera_context) {
    if (API::OPENGL == Backend::GetAPI()) { OpenGLRenderer::UpdateViewportBuffers(new_scene_context, new_camera_context); }
}

} // namespace Renderer
