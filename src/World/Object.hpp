#pragma once

#include "Math/Matrix.hpp"
#include "ResourceHandling/Types/Common.hpp"

namespace World {

// This is an object to be rendered
// - it does not own any actual data
// - it just looks at it at runtime
class Object {
private:
    // the pointers may change, but the underlying data must never be changed by a World::Object
    const LoadedModelData *model_view_;
    const MaterialData *material_view_;
    const TextureData *texture_view_;

    Matrix4 transform_;

public:
    Object(const LoadedModelData *model);
    Object(const LoadedModelData *model, const MaterialData *material);
    Object(const LoadedModelData *model, const MaterialData *material, const TextureData *texture);

    const Matrix4 &GetTransform() const noexcept { return transform_; }
    const LoadedModelData *GetModel() const noexcept { return model_view_; }
};

} // namespace World
