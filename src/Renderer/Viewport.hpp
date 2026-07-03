#pragma once

#include "Math/Matrix.hpp"
#include "Util/Aliases.hpp"
#include "World/Camera.hpp"
#include "World/Scene.hpp"

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
    const World::Camera *camera_;
    const World::Scene *scene_;
    f32 x_{0.0f};
    f32 y_{0.0f};
    f32 width_{800.0f};
    f32 height_{600.0f};

public:
    Viewport() = default;
    Viewport(const World::Camera *camera, const World::Scene *scene, f32 x, f32 y, f32 width_, f32 height_);

    ViewportGPUData BuildGPUData() const;


    const World::Camera *GetCamera() const { return camera_; }
    const World::Scene *GetScene() const { return scene_; }
    f32 AspectRatio() const { return (height_ > 0.0f) ? width_ / height_ : 1.0f; }
};

} // namespace Renderer
