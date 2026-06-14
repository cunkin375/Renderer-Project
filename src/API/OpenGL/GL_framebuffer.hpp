#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App/Types.hpp"

namespace OpenGL {
    namespace GLFW {
        void FramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
    }
}

