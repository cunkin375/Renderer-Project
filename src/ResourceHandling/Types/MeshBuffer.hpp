#pragma once

#include <cstdint>

struct MeshBuffer {
    MeshBuffer() {}

    // OpenGL
    std::uint32_t GetVAO() const;
    std::uint32_t GetVBO() const;
    std::uint32_t GetEBO() const;
};
