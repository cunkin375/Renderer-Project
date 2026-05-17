#pragma once
#include "App/Enums.hpp"

namespace Backend {
    bool Init(API api, WindowMode window_mode);
    void BeginFrame();
    void EndFrame();
    bool WindowIsOpen();
}
