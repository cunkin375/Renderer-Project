#include "Camera.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace World {

Camera::Camera(const Vector3 &position, const Vector3 &look_at, const Vector3 &up, f32 fov, f32 near_plane,
               f32 far_plane) {}

std::span<const f32> Camera::View() const { return {}; }

std::span<const f32> Camera::Projection() const { return {}; }

Matrix4 Camera::ViewMatrix() const { return {}; }

Matrix4 Camera::ProjectionMatrix(f32 aspect_ratio) const { return {}; }

} // namespace World
