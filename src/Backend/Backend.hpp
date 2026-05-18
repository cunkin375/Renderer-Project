#pragma once

#include "WindowHandle.hpp"
#include "App/Enums.hpp"

namespace Backend {
    bool Init(API api, WindowMode window_mode);
    bool WindowIsOpen();
    API GetAPI();
    WindowHandle GetWindowPointer();
    void BeginFrame();
    void EndFrame();
}
