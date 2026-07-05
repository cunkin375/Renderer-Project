#pragma once

#include "Math/Matrix.hpp"
#include "Util/Aliases.hpp"

namespace Renderer {

struct alignas(16) ViewportGPUData {
    Matrix4 view;
    Matrix4 projection;
    f32 screen_x;
    f32 screen_y;
    f32 screen_width;
    f32 screen_height;
};
static_assert(sizeof(ViewportGPUData) == 144);

struct Viewport {
private:
    f32 x_{0.0f};
    f32 y_{0.0f};
    f32 width_{800.0f};
    f32 height_{600.0f};

public:
    Viewport() = default;
    Viewport(f32 x, f32 y, f32 width, f32 height);

    ViewportGPUData CopyBuildGPUData(const std::array<f32, 16zu> &view, const std::array<f32, 16zu> &projection) const;

    ViewportGPUData MoveBuildGPUData(const std::array<f32, 16zu> &&view, const std::array<f32, 16zu> &&projection) const;

};

} // namespace Renderer
