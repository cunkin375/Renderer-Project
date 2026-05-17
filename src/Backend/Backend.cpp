#include "Backend.hpp"

#include <GLFW/glfw3.h>

namespace Backend {
    API g_api = API::UNDEFINED;

    bool Init(API api, WindowMode window_mode) {
        return true;
    }

    void BeginFrame();
    void EndFrame();
    bool WindowIsOpen();
}
