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
           f32 near_plane, f32 far_plane);

    std::span<const f32> View() const noexcept { return view_.GetSpan(); }
    std::span<const f32> Projection() const noexcept { return projection_.GetSpan(); }
};

} // namespace World
