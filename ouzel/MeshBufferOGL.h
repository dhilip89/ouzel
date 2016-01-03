// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "CompileConfig.h"

#if defined(OUZEL_PLATFORM_OSX)
#include <OpenGL/gl3.h>
#elif defined(OUZEL_PLATFORM_IOS)
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

#include "MeshBuffer.h"

namespace ouzel
{
    class RendererOGL;
    
    class MeshBufferOGL: public MeshBuffer
    {
        friend RendererOGL;
    public:
        virtual ~MeshBufferOGL();
        
        virtual bool initFromData(const void* indices, uint32_t indexSize, uint32_t indexCount, bool dynamicIndexBuffer, const void* vertices, uint32_t vertexSize, uint32_t vertexCount, bool dynamicVertexBuffer, uint32_t vertexAttributes) override;
        
        virtual bool uploadIndices(const void* indices, uint32_t indexCount) override;
        virtual bool uploadVertices(const void* vertices, uint32_t vertexCount) override;
        
        GLuint getIndexBufferId() const { return _indexBufferId; }
        GLuint getVertexArrayId() const { return _vertexArrayId; }
        
        GLsizei getIndexCount() const { return _indexCount; }
        GLenum getIndexFormat() const { return _indexFormat; }
        
    protected:
        MeshBufferOGL();
        
        GLuint _vertexArrayId = 0;
        GLuint _indexBufferId = 0;
        GLuint _vertexBufferId = 0;
        
        GLsizei _indexCount = 0;
        GLenum _indexFormat = 0;
    };
}
