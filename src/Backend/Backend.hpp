#pragma once

#include "Util/Enums.hpp"
#include "WindowHandle.hpp"

namespace Backend {
    bool Init(API api, WindowMode window_mode);
    bool WindowIsOpen();
    API GetAPI();
    WindowHandle GetWindowPointer();
    void BeginFrame();
    void EndFrame();
    void Update();
    void Destroy();
} // namespace Backend
