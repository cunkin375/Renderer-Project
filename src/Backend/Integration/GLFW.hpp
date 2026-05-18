#pragma once
#include "App/Enums.hpp"
#include "../WindowHandle.hpp"

namespace Backend::GLFW {
    WindowHandle GetWindowPointer();
    bool Init(API api, WindowMode window_mode);
    bool WindowIsOpen();
    void Destroy();
}
