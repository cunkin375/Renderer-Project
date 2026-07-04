#pragma once

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Util/Aliases.hpp"

#include <span>

namespace World {

struct FrustumPlane {
    Vector3 normal;
    f32 offset;
};

struct Frustum {};

class Camera {
private:
    Vector3 position_;
    Vector3 look_at_;
    Vector3 up_;
    f32 fov_;
    f32 near_plane_;
    f32 far_plane_;

public:
    Camera() = default;

    Camera(const Vector3 &position, const Vector3 &look_at, const Vector3 &up, f32 fov, f32 near_plane,
           f32 far_plane);

    std::span<const f32> View() const;
    std::span<const f32> Projection() const;

    Matrix4 ViewMatrix() const;
    Matrix4 ProjectionMatrix(f32 aspect_ratio) const;

    Vector3 Position() const noexcept { return position_; }
    Vector3 LookAt() const noexcept { return look_at_; }
    Vector3 Up() const noexcept { return up_; }
    f32 FOV() const noexcept { return fov_; }
    f32 NearPlane() const noexcept { return near_plane_; }
    f32 FarPlane() const noexcept { return far_plane_; }
};

} // namespace World
