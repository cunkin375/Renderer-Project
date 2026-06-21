#pragma once

#include <vector>

#include "ResourceHandling/Types/Common.hpp"

namespace OpenGLBackend {
    void Init();
    void BeginFrame();
    void UploadVertexData(std::vector<VertexData> vertices, std::vector<IndexData> indices);

} // namespace OpenGLBackend
