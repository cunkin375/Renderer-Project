#pragma once

#include <vector>
#include <memory>

#include "World/Object.hpp"

namespace World {

struct Scene {
    // keep this light, it may also change as methods for rendering scenes change
    // TODO: look into managing this information using an arena / bump allocations
    std::vector<std::unique_ptr<Object>> objects{};
};

} // namespace World
