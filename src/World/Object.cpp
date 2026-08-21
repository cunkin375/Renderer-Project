#include "Object.hpp"

namespace World
{

Object::Object(const LoadedModelData *model) : model_view_{ model } {}

Object::Object(const LoadedModelData *model, const MaterialData *material)
    : model_view_{ model }, material_view_{ material }
{
}

Object::Object(const LoadedModelData *model, const MaterialData *material, const TextureData *texture)
    : model_view_{ model }, material_view_{ material }, texture_view_{ texture }
{
}

} // namespace World
