#include "Renderer.hpp"

#include "API/OpenGL/GL_Renderer.hpp"
#include "Backend/Backend.hpp"
#include "Viewport.hpp"

#include "Util/StringHash.hpp"

namespace Renderer {
auto g_meshes = StringMap<u64>{};

void Render() {
    if (API::OPENGL == Backend::GetAPI()) {
        // TODO: THIS IS TEMPORARY AND ONLY MEANT TO PROTOTYPE, VIEWPORT INFORMATION SHOULD BE STORED AND USED
        // IN AN SSBO
        OpenGLRenderer::Render();
    }
}

void Init() {
    UploadVertexData();
}

void UploadVertexData() {
    if (Backend::GetAPI() == API::OPENGL) {}
}

void ReloadShaders() {
    if (API::OPENGL == Backend::GetAPI()) { OpenGLRenderer::ReloadShaders(); }
}

} // namespace Renderer
