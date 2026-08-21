#include "GL_Framebuffer.hpp"

namespace OpenGL
{
namespace GLFW
{
    void FramebufferSizeCallback(GLFWwindow *window, i32 width, i32 height)
    {
        glViewport(0, 0, width, height);
    }
} // namespace GLFW
} // namespace OpenGL
