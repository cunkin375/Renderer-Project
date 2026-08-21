#include "Camera.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

#include "Renderer/Viewport.hpp"

namespace World
{

Camera::Camera(const fVector3 &position, const fVector3 &look_at, const fVector3 &up, f32 fov, f32 near_plane,
               f32 far_plane)
    : position_{ position }, look_at_{ look_at }, up_{ up }, fov_{ fov }, near_plane_{ near_plane },
      far_plane_{ far_plane }
{
}

std::span<const f32> Camera::View() const
{
    static thread_local auto cached_view = Matrix4{};
    cached_view = ViewMatrix();
    return cached_view.GetSpan();
}

std::span<const f32> Camera::Projection(f32 aspect_ratio) const
{
    static thread_local auto cached_projection = Matrix4{};
    cached_projection = ProjectionMatrix(aspect_ratio);
    return cached_projection.GetSpan();
}

Matrix4 Camera::ViewMatrix() const { return Matrix4::LookAt(position_, look_at_, up_); }

Matrix4 Camera::ProjectionMatrix(f32 aspect_ratio) const
{
    return Matrix4::Perspective(fov_, aspect_ratio, 1.0f, near_plane_, far_plane_);
}

} // namespace World
