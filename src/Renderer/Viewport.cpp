#include "Viewport.hpp"

namespace Renderer {

// this could move the camera into the viewport object? too early to know
Viewport::Viewport(const World::Camera &camera) : camera_{camera} {}

}
