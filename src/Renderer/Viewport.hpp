#pragma once

#include "World/Camera.hpp"

namespace Renderer {

struct Viewport {
private:
    World::Camera camera_;

public:
    Viewport() = default;
    Viewport(const World::Camera &camera);

    World::Camera &GetCamera() { return camera_; }
};


}

