#pragma once

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Util/Aliases.hpp"

#include <span>

namespace World {

struct FrustumPlane {
    fVector3 normal;
    f32 offset;
};

struct Frustum {};

class Camera {
private:
    fVector3 position_;
    fVector3 look_at_;
    fVector3 up_;
    f32 fov_;
    f32 near_plane_;
    f32 far_plane_;

public:
    Camera() = default;

    Camera(const fVector3 &position, const fVector3 &look_at, const fVector3 &up, f32 fov, f32 near_plane,
           f32 far_plane);

    std::span<const f32> View() const;
    std::span<const f32> Projection(f32 aspect_ratio) const;

    Matrix4 ViewMatrix() const;
    Matrix4 ProjectionMatrix(f32 aspect_ratio) const;

    fVector3 Position() const noexcept { return position_; }
    fVector3 LookAt() const noexcept { return look_at_; }
    fVector3 Up() const noexcept { return up_; }
    f32 FOV() const noexcept { return fov_; }
    f32 NearPlane() const noexcept { return near_plane_; }
    f32 FarPlane() const noexcept { return far_plane_; }

};

} // namespace World
