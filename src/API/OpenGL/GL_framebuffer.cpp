#include "GL_Framebuffer.hpp"

namespace OpenGL {
    namespace GLFW {
        void framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
        {
            glViewport(0, 0, width, height);
        }
    }
}
