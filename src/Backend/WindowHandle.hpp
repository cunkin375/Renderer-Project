#pragma once

struct GLFWwindow;

namespace Backend {
// WindowHandle wrapper meant to support multiple APIS. Currently supports GLFW.
class WindowHandle {
private:
    void *handle = nullptr;

public:
    // Prevent implicit conversions from compiler
    explicit WindowHandle(void *h) : handle(h) {}

    // template method for type access
    template <typename T>
    T *as() const {
        return static_cast<T *>(handle);
    }

    GLFWwindow *asGLFW() const { return as<GLFWwindow>(); }

    // For use in "if (!WindowHandle) {...}" checks
    explicit operator bool() const { return handle != nullptr; }
};
} // namespace Backend
