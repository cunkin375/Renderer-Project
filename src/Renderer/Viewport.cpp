#include "Viewport.hpp"

namespace Renderer {

Viewport::Viewport(const World::Camera *camera, const World::Scene *scene, f32 x, f32 y, f32 width,
                   f32 height)
    : camera_{camera}, scene_{scene}, x_{x}, y_{y}, width_{width}, height_{height} {}

ViewportGPUData Viewport::BuildGPUData() const {
    return ViewportGPUData{
        .view = camera_->ViewMatrix(),
        .projection = camera_->ProjectionMatrix(AspectRatio()),
        .screen_x = x_,
        .screen_y = y_,
    };
}

} // namespace Renderer
