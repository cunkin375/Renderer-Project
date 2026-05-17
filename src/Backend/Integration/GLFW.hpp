#pragma once
#include "App/Enums.hpp"

namespace Backend::GLFW {
    bool Init(API api, WindowMode window_mode);
    bool WindowIsOpen();
    void Destroy();
}
