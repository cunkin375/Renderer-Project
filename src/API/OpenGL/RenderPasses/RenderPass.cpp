#include "../RenderPasses.hpp"

#include <glad/glad.h>

#include "../Types/GL_MeshBuffer.hpp"
#include "ResourceHandling/ResourceManager.hpp"

namespace OpenGLRenderer {
    extern std::vector<OpenGLMeshBuffer> g_meshes;

    void RenderPass() {
        auto info = ResourceManager::GetGPUModelInfo("resources/models/triangle.obj");
        if (info.has_value() && info->index_count > 0) {
            g_meshes[info->handle].Bind();
            glDrawElements(GL_TRIANGLES, info->index_count, GL_UNSIGNED_INT, 0);
            g_meshes[info->handle].Unbind();
        }
    }
} // namespace OpenGLRenderer
