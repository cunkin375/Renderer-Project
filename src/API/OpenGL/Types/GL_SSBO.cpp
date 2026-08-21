#include "GL_SSBO.hpp"

OpenGLSSBO::OpenGLSSBO(const ObjectBuffer size, const GLbitfield flags_bitmask)
    : flags_bitmask_{ flags_bitmask }
{
    Reserve(size);
}

void OpenGLSSBO::Reserve(const ObjectBuffer size)
{
    // skip if we dont need more space
    if (handle_ != 0 && buffer_size_ >= size)
    {
        return;
    }

    CleanUp();

    glCreateBuffers(1, &handle_);
    glNamedBufferStorage(handle_, static_cast<GLsizeiptr>(size), nullptr, flags_bitmask_);
    buffer_size_ = size;
}

void OpenGLSSBO::Update(ObjectBuffer size, const void *data)
{
    if (size == 0 || data == nullptr)
    {
        return;
    }

    Reserve(size);

    glNamedBufferSubData(handle_, 0, static_cast<GLsizeiptr>(size), data);
}

void OpenGLSSBO::UploadStatic(ObjectBuffer size, const void *data)
{
    if (size == 0 || data == nullptr)
    {
        return;
    }

    CleanUp();

    glCreateBuffers(1, &handle_);
}

void OpenGLSSBO::Bind(ObjectHandle index) const
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, handle_);
}

void OpenGLSSBO::CleanUp()
{
    if (handle_ != 0)
    {
        glDeleteBuffers(1, &handle_);
        handle_ = 0;
        buffer_size_ = 0;
    }
}

void OpenGLSSBO::CopyFrom(const void *host_pointer, std::size_t size_in_bytes)
{
    if (!host_pointer || size_in_bytes == 0 || handle_ == 0)
    {
        return;
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, handle_);
}

void OpenGLSSBO::Clear() const
{
    if (handle_ == 0)
    {
        return;
    }

    u32 zero = 0;
    glClearNamedBufferData(handle_, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
}

void OpenGLSSBO::ClearRange(std::size_t offset, ObjectBuffer size)
{
    if (handle_ == 0)
    {
        return;
    }

    std::size_t actual_size = (offset + size > buffer_size_) ? (buffer_size_ - offset) : size;
    u32 zero = 0;
    glClearNamedBufferSubData(handle_, GL_R32UI, static_cast<GLintptr>(offset),
                              static_cast<GLsizeiptr>(actual_size), GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
}
