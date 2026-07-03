#pragma once

#include "World/Camera.hpp"

namespace Renderer {

struct Viewport {
private:
    World::Camera camera_;

public:
    Viewport() = default;
    Viewport(const World::Camera &camera);

    const World::Camera &GetCamera() const { return camera_; }
};


}

