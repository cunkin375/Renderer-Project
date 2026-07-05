#include "Viewport.hpp"

namespace Renderer {

Viewport::Viewport(f32 x, f32 y, f32 width, f32 height) : x_{x}, y_{y}, width_{width}, height_{height} {}

ViewportGPUData Viewport::CopyBuildGPUData(const std::array<f32, 16zu> &view, const std::array<f32, 16zu> &projection) const {
    return ViewportGPUData{
        .view = Matrix4{view},
        .projection = Matrix4{projection},
        .screen_x = x_,
        .screen_y = y_,
    };
}

ViewportGPUData Viewport::MoveBuildGPUData(const std::array<f32, 16zu> &&view, const std::array<f32, 16zu> &&projection) const {
    return ViewportGPUData{
        .view = Matrix4{view},
        .projection = Matrix4{projection},
        .screen_x = x_,
        .screen_y = y_,
    };
}

} // namespace Renderer
