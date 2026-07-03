#pragma once

#include "Math/Matrix.hpp"
#include "ResourceHandling/Types/Common.hpp"

#include <string_view>

namespace World {

// This is an object to be rendered
// - it does not own any actual data
// - it just looks at it at runtime
class Object {
private:
    // the pointers may change, but the underlying data must never be changed by a World::Object
    const ModelData *model_view_;
    const MaterialData *material_view_;
    const TextureData *texture_view_;

    Matrix4 transform_;

public:
    Object(const ModelData *model, const MaterialData *material);

    Object(const ModelData *model, const MaterialData *material, const TextureData *texture);

    std::string_view GetModelName();
    Matrix4 &GetTransform();
};

} // namespace World
