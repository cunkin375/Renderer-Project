#pragma once

#include <glad/glad.h>
#include <vector>

#include "App/Types.hpp"


struct OpenGLMeshBuffer {
private:
    GLuint VAO_ = 0;
    GLuint VBO_ = 0;
    GLuint EBO_ = 0;
    GLsizei vertex_count_ = 0;
    GLsizei index_count_ = 0;
    GLsizei allocated_vertex_count_ = 0;
    GLsizei allocated_index_count_ = 0;

public:
    void ReleaseBuffers();
    void UpdateBuffers(std::vector<Vertex>& vertices);
};
