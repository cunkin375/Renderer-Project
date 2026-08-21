#include "Object.hpp"
#include <cassert>

namespace World
{

Object::Object(const LoadedModelData *model) : model_view_{ model }
{
    assert(model_view_ != nullptr && "Object initialized with null model");
}

Object::Object(const LoadedModelData *model, const MaterialData *material)
    : model_view_{ model }, material_view_{ material }
{
    assert(model_view_ != nullptr && "Object initialized with null model");
}

Object::Object(const LoadedModelData *model, const MaterialData *material, const TextureData *texture)
    : model_view_{ model }, material_view_{ material }, texture_view_{ texture }
{
    assert(model_view_ != nullptr && "Object initialized with null model");
}

} // namespace World
