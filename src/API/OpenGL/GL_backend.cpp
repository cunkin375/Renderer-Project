#include "GL_backend.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace OpenGLBackend {
    void Init()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            return;
        }
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        std::cout << "GPU: " << renderer << "\n";
        std::cout << "OpenGL vendor: " << vendor << "\n";
        std::cout << "OpenGL version: " << major << "." << minor << "\n";
    }

    void BeginFrame()
    {
    }
}
