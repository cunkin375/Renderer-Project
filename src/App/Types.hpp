#pragma once

#include "Math/Vector.hpp"

#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;

using u32 = std::uint32_t;
using u64 = std::uint64_t;

using ivec2 = Math::Vector<2zu, i32>;

struct Resolution {
    ivec2 size;
};

struct Vertex {

};
