#pragma once
#include "../WindowHandle.hpp"
#include "Util/Enums.hpp"
#include "Util/Aliases.hpp"

namespace Backend::GLFW {
    WindowHandle GetWindowPointer();
    bool Init(API api, WindowMode window_mode);
    void Destroy();
    void BeginFrame(API api);
    void EndFrame(API api);
    void Update();
    bool WindowIsOpen();
    u32 GetTime();
    void MakeContextCurrent();
    void ShowWindow(GLFWwindow *window);
} // namespace Backend::GLFW
