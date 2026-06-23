#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

#include "ResourceHandling/Types/Common.hpp"
#include "Util/AutoRelease.hpp"

struct OpenGLMeshBuffer {
private:
    AutoRelease<GLuint> vao_{};
    AutoRelease<GLuint> vbo_{};
    AutoRelease<GLuint> ebo_{};
    GLsizei vertex_stride_{};

public:
    OpenGLMeshBuffer(const ModelData &data);
    OpenGLMeshBuffer(const ModelData &data, const std::string &name);
    void Load(const ModelData &data, const std::string &name = {});
    void Bind();
    void Unbind();
    void ReleaseBuffers();
    void UpdateBuffers(std::vector<VertexData> &vertices);
};
