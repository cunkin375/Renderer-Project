#include "GLFW.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

namespace Backend::GLFW {
    GLFWwindow* g_window = nullptr;

    bool Init(API api, WindowMode window_mode) 
    {
        glfwSetErrorCallback([](int error, const char* description) {
            std::cerr << "GLFW Error " << error << ": " << description << "\n";
        });

        glfwInit();

        /// GLFW version: 4.6
        if (api == API::OPENGL)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            glfwWindowHint(GLFW_SAMPLES, 0);
        }
        
        return true;
    }

    bool WindowIsOpen()
    {
        return false;
    }

    WindowHandle GetWindowPointer()
    {
        return WindowHandle(g_window);
    }

    void Destroy();
}
