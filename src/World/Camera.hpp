#pragma once

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Util/Aliases.hpp"

namespace World {

struct FrustumPlane {
    Vector3 normal;
    f32 offset;
};

struct Frustum {};

class Camera {
private:
    Matrix4 view_;
    Matrix4 projection_;

public:
    Camera() = default;

    Camera(const Vector3 &position, const Vector3 &look_at, const Vector3 &up, f32 fov, f32 width, f32 height,
           f32 near_plane, f32 far_plane)
        : view_{Matrix4::LookAt(position, look_at, up)},
          projection_{Matrix4::Perspective(fov, width, height, near_plane, far_plane)} {}

    std::span<const f32> View() const { return view_.GetSpan(); }
    std::span<const f32> Projection() const { return projection_.GetSpan(); }
};

} // namespace World
