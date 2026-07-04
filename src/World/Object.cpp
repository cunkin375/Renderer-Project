#include "Object.hpp"

namespace World {

Object::Object(const ModelData *model)
    : model_view_{model} {}

Object::Object(const ModelData *model, const MaterialData *material)
    : model_view_{model}, material_view_{material} {}

Object::Object(const ModelData *model, const MaterialData *material, const TextureData *texture)
    : model_view_{model}, material_view_{material}, texture_view_{texture} {}

} // namespace World
