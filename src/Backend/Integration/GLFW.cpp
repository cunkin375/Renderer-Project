#include "GLFW.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "API/OpenGL/GL_framebuffer.hpp"
#include "Define/Types.hpp"

namespace Backend::GLFW {
    const GLFWvidmode *g_mode;
    GLFWwindow *g_window = nullptr;
    GLFWmonitor *g_monitor = nullptr;
    WindowMode g_window_mode = WindowMode::WINDOWED;

    auto g_windowed_height = i32{};
    auto g_windowed_width = i32{};
    auto g_fullscreen_height = i32{};
    auto g_fullscreen_width = i32{};
    auto g_current_window_width = i32{};
    auto g_current_window_height = i32{};
    auto g_force_close_window = bool{};

    bool Init(API api, WindowMode window_mode) {
        glfwSetErrorCallback([](i32 error, const char *description) {
            std::cerr << "GLFW Error " << error << ": " << description << "\n";
        });

        glfwInit();

        /// GLFW version: 4.6
        if (api == API::OPENGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            glfwWindowHint(GLFW_SAMPLES, 0);
        }

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Set resolution and window size
        g_monitor = glfwGetPrimaryMonitor();
        g_mode = glfwGetVideoMode(g_monitor);
        glfwWindowHint(GLFW_RED_BITS, g_mode->redBits);
        glfwWindowHint(GLFW_BLUE_BITS, g_mode->blueBits);
        glfwWindowHint(GLFW_GREEN_BITS, g_mode->greenBits);
        glfwWindowHint(GLFW_REFRESH_RATE, g_mode->refreshRate);
        g_fullscreen_width = g_mode->width;
        g_fullscreen_height = g_mode->height;
        g_windowed_width = g_fullscreen_width * 0.75f;
        g_windowed_height = g_fullscreen_height * 0.75f;

        // Create window
        g_window_mode = window_mode;
        if (g_window_mode == WindowMode::WINDOWED) {
            g_current_window_width = g_windowed_width;
            g_current_window_height = g_windowed_height;
            g_window = glfwCreateWindow(g_windowed_width, g_windowed_height,
                                        "GLFW Window", nullptr, nullptr);
            glfwSetWindowPos(g_window, 0, 0);
        } else if (g_window_mode == WindowMode::FULLSCREEN) {
            g_current_window_width = g_fullscreen_width;
            g_current_window_height = g_fullscreen_height;
            g_window = glfwCreateWindow(g_fullscreen_width, g_fullscreen_height,
                                        "GLFW Window", g_monitor, nullptr);
        }
        if (g_window == nullptr) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return false;
        }
        if (api == API::OPENGL) {
            glfwSetFramebufferSizeCallback(
                g_window, OpenGL::GLFW::FramebufferSizeCallback);
        }

        return true;
    }

    void Destroy() { glfwTerminate(); }

    void BeginFrame(API api) {
        if (api == API::OPENGL) {
            glfwPollEvents();
        }
    }

    void EndFrame(API api) {
        if (api == API::OPENGL) {
            glfwSwapBuffers(g_window);
        }
    }

    void Update() {
        if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(g_window, true);
        }
    }

    bool WindowIsOpen() {
        return (!glfwWindowShouldClose(g_window) || g_force_close_window);
    }

    u32 GetTime() { return glfwGetTime(); }

    WindowHandle GetWindowPointer() { return WindowHandle(g_window); }

    void MakeContextCurrent() { glfwMakeContextCurrent(g_window); }

    void ShowWindow(GLFWwindow *window) { glfwShowWindow(window); }

} // namespace Backend::GLFW
