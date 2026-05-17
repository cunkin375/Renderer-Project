#include "GLFW.hpp"

namespace Backend::GLFW {
    bool Init(API api, WindowMode window_mode) 
    {
        return true;
    }

    bool WindowIsOpen()
    {
        return false;
    }
    void Destroy();
}
