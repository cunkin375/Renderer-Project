#include "Viewport.hpp"

namespace Renderer {

Viewport::Viewport(f32 x, f32 y, f32 width,
                   f32 height)
    : x_{x}, y_{y}, width_{width}, height_{height} {}

ViewportGPUData Viewport::BuildGPUData() const {
    return ViewportGPUData{
        .screen_x = x_,
        .screen_y = y_,
    };
}

} // namespace Renderer
