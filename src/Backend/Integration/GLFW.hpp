#pragma once
#include "App/Enums.hpp"
#include "../WindowHandle.hpp"

namespace Backend::GLFW {
    bool Init(API api, WindowMode window_mode);
    bool WindowIsOpen();
    void Destroy();
    WindowHandle GetWindowPointer();
}
