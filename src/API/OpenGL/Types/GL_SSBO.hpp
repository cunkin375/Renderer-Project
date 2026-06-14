#pragma once

#include "App/Types.hpp"

#include <glad/glad.h>

using ObjectHandle = u32;
using ObjectBuffer = std::size_t;

// TODO: implement this
struct OpenGLSSBO {
private:
    ObjectHandle handle_{};
    ObjectBuffer buffer_size_{};
    GLbitfield flags_bitmask_{};

public:
    OpenGLSSBO() = default;
    OpenGLSSBO(ObjectBuffer size, GLbitfield flags_bitmask);

    void Reserve(ObjectBuffer size);
    void Update(ObjectBuffer size, const void* data);
    void UploadStatic(ObjectBuffer size, const void* data);
    void Bind(ObjectHandle index) const;
    void CleanUp();
    void CopyFrom(const void* host_pointer, std::size_t size_in_bytes);
    void Clear() const;
    void ClearRange(std::size_t offset, ObjectBuffer size);

    const ObjectHandle GetHandle() const { return handle_; }
    const ObjectBuffer GetSize() const { return buffer_size_; }

};
