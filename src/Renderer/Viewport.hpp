#pragma once

#include "World/Camera.hpp"

struct Viewport {
private:
    World::Camera camera;

public:
    Viewport() = default;
    Viewport(const World::Camera &camera) : camera(camera) {}
};

