#include "GL_MeshBuffer.hpp"

#include "Util/AutoRelease.hpp"

OpenGLMeshBuffer::OpenGLMeshBuffer(const ModelData &data)
    :  vao_{
        []()-> GLuint { auto vao = GLuint{}; glCreateVertexArrays(1, &vao); return vao; }(), 
        [](auto vao) { glDeleteVertexArrays(1, &vao); } 
    }, vbo_{
        []()-> GLuint { auto vbo = GLuint{}; glCreateBuffers(1, &vbo); return vbo; }(), 
        [](auto vbo) { glDeleteBuffers(1, &vbo); }
    }, ebo_{
        []()-> GLuint { auto ebo = GLuint{}; glCreateBuffers(1, &ebo); return ebo; }(), 
        [](auto ebo) { glDeleteBuffers(1, &ebo); }
    }, vertex_stride_{sizeof(f32) * 3}
{
    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size_bytes(), data.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size_bytes(), data.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void OpenGLMeshBuffer::Bind() { glBindVertexArray(vao_); }

void OpenGLMeshBuffer::Unbind() { glBindVertexArray(0); }
