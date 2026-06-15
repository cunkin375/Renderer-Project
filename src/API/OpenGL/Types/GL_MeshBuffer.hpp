#pragma once

#include <glad/glad.h>
#include <vector>

#include "Define/Types.hpp"

struct OpenGLMeshBuffer {
private:
    GLuint VAO_{};
    GLuint VBO_{};
    GLuint EBO_{};
    GLsizei vertex_count_{};
    GLsizei index_count_{};
    GLsizei allocated_vertex_count_{};
    GLsizei allocated_index_count_{};

public:
    void ReleaseBuffers();
    void UpdateBuffers(std::vector<Vertex> &vertices);
};
