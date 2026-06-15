#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Define/Types.hpp"

namespace OpenGL {
    namespace GLFW {
        void FramebufferSizeCallback(GLFWwindow *window, i32 width, i32 height);
    }
} // namespace OpenGL
