#include "GL_Backend.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace {
    void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* userParam)
    {
        // Ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cerr << "---------------\n";
        std::cerr << "OpenGL Debug Message (" << id << "): " << message << "\n";

        switch (source) {
            case GL_DEBUG_SOURCE_API:             std::cerr << "Source: API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Source: Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Source: Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Source: Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Source: Application"; break;
            case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Source: Other"; break;
        } std::cerr << "\n";

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:               std::cerr << "Type: Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Type: Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Type: Undefined Behaviour"; break; 
            case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Type: Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Type: Performance"; break;
            case GL_DEBUG_TYPE_MARKER:              std::cerr << "Type: Marker"; break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Type: Push Group"; break;
            case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Type: Pop Group"; break;
            case GL_DEBUG_TYPE_OTHER:               std::cerr << "Type: Other"; break;
        } std::cerr << "\n";

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: High"; break;
            case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: Medium"; break;
            case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: Low"; break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: Notification"; break;
        } std::cerr << "\n\n";

        // Automatically trigger breakpoint in IDE when high-severity error
        if (severity == GL_DEBUG_SEVERITY_HIGH) {
            #ifdef _MSC_VER
                __debugbreak(); // Visual Studio
            #else
                __builtin_trap(); // GCC/Clang
            #endif
        }
    }

}

namespace OpenGLBackend {
    void Init() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return;
        }

        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        const GLubyte *vendor = glGetString(GL_VENDOR);
        const GLubyte *renderer = glGetString(GL_RENDERER);
        std::cout << "GPU: " << renderer << "\n";
        std::cout << "OpenGL vendor: " << vendor << "\n";
        std::cout << "OpenGL version: " << major << "." << minor << "\n";

        // Debug information
        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAG_DEBUG_BIT, &flags);

        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(OpenGLDebugCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }

    void BeginFrame() { glClear(GL_COLOR_BUFFER_BIT); }

} // namespace OpenGLBackend
