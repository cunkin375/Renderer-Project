#include "GL_MeshBuffer.hpp"

#include "ResourceHandling/Types/Common.hpp"
#include "Util/AutoRelease.hpp"

namespace {
using NumVAOs = GLsizei;
using NumVBOs = GLsizei;
using NumEBOs = GLsizei;

using Index = GLuint;
using BindingIndex = Index;
using AttributeIndex = Index;

using Offset = GLintptr;
using Stride = GLsizei;
using Size = GLint;
} // namespace

OpenGLMeshBuffer::OpenGLMeshBuffer(const ModelData &data)
    : vao_{[]() -> GLuint {
               auto vao = GLuint{};
               glCreateVertexArrays(NumVAOs{1}, &vao);
               return vao;
           }(),
           [](auto vao) { glDeleteVertexArrays(NumVAOs{1}, &vao); }

      },
      vbo_{[]() -> GLuint {
               auto vbo = GLuint{};
               glCreateBuffers(NumVBOs{1}, &vbo);
               return vbo;
           }(),
           [](auto vbo) { glDeleteBuffers(NumVBOs{1}, &vbo); }

      },
      ebo_{[]() -> GLuint {
               auto ebo = GLuint{};
               glCreateBuffers(NumEBOs{1}, &ebo);
               return ebo;
           }(),
           [](auto ebo) { glDeleteBuffers(NumEBOs{1}, &ebo); }

      },
      vertex_stride_{sizeof(VertexData)} {
    Load(data);
}

OpenGLMeshBuffer::OpenGLMeshBuffer(const ModelData &data, const std::string &name)
    : vao_{[]() -> GLuint {
               auto vao = GLuint{};
               glCreateVertexArrays(NumVAOs{1}, &vao);
               return vao;
           }(),
           [](auto vao) { glDeleteVertexArrays(NumVAOs{1}, &vao); }

      },
      vbo_{[]() -> GLuint {
               auto vbo = GLuint{};
               glCreateBuffers(NumVBOs{1}, &vbo);
               return vbo;
           }(),
           [](auto vbo) { glDeleteBuffers(NumVBOs{1}, &vbo); }

      },
      ebo_{[]() -> GLuint {
               auto ebo = GLuint{};
               glCreateBuffers(NumEBOs{1}, &ebo);
               return ebo;
           }(),
           [](auto ebo) { glDeleteBuffers(NumEBOs{1}, &ebo); }

      },
      vertex_stride_{sizeof(VertexData)} {
    Load(data, name);
}

void OpenGLMeshBuffer::Load(const ModelData &data, const std::string &name) {
    glNamedBufferStorage(vbo_, data.vertices.size_bytes(), data.vertices.data(), 0);
    glNamedBufferStorage(ebo_, data.indices.size_bytes(), data.indices.data(), 0);

    glVertexArrayVertexBuffer(vao_, BindingIndex{0}, vbo_, Offset{0}, Stride{vertex_stride_});

    glVertexArrayElementBuffer(vao_, ebo_);

    // Position attribute
    glEnableVertexArrayAttrib(vao_, Index{0});
    glVertexArrayAttribFormat(vao_, AttributeIndex{0}, Size{3}, GL_FLOAT, GL_FALSE,
                              offsetof(VertexData, position));
    glVertexArrayAttribBinding(vao_, AttributeIndex{0}, BindingIndex{0});

    // Color attribute
    glEnableVertexArrayAttrib(vao_, Index{1});
    glVertexArrayAttribFormat(vao_, AttributeIndex{1}, Size{3}, GL_FLOAT, GL_FALSE,
                              offsetof(VertexData, color));
    glVertexArrayAttribBinding(vao_, AttributeIndex{1}, BindingIndex{0});

    if (name.length()) {
        glObjectLabel(GL_BUFFER, vbo_, static_cast<GLsizei>(name.length()), name.c_str());
    }
}

void OpenGLMeshBuffer::Bind() { glBindVertexArray(vao_); }

void OpenGLMeshBuffer::Unbind() { glBindVertexArray(0); }
