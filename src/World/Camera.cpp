#include "Camera.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace World {

Camera::Camera(const Vector3 &position, const Vector3 &look_at, const Vector3 &up, f32 fov, f32 width,
               f32 height, f32 near_plane, f32 far_plane)
    : view_{Matrix4::LookAt(position, look_at, up)},
      projection_{Matrix4::Perspective(fov, width, height, near_plane, far_plane)} {}

} // namespace World
