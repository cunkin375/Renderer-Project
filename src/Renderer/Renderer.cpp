#include "Renderer.hpp"

#include "API/OpenGL/GL_Renderer.hpp"
#include "Backend/Backend.hpp"

namespace Renderer {
    void Render() {
        if (API::OPENGL == Backend::GetAPI()) {
            OpenGLRenderer::Render();
        }
    }

    void Init() { UploadVertexData(); }

    void UploadVertexData() {
        if (Backend::GetAPI() == API::OPENGL) {
            OpenGLRenderer::UploadVertexData();
        }
    }

    void ReloadShaders() {
        if (API::OPENGL == Backend::GetAPI()) {
            OpenGLRenderer::ReloadShaders();
        }
    }

} // namespace Renderer
