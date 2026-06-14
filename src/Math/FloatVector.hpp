#pragma once

// I would love to use this, unfortunately, my clangd lsp is being a piece of shit
// #include <stdfloat>

// Should almost never fail but I would like to know when it does
static_assert(sizeof(float) == 4,  "32-bit float is required for Math/FloatVector.hpp!");
static_assert(sizeof(double) == 8, "64-bit double is required for Math/FloatVector.hpp!");

namespace Math {

struct FloatVector2 {
    float x;
    float y;
};

struct FloatVector3 {
    float x;
    float y;
    float z;
};

}
