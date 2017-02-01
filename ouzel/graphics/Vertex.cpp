// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "Vertex.h"

namespace ouzel
{
    namespace graphics
    {
        const std::vector<VertexAttribute> VertexPC::ATTRIBUTES = {
            VertexAttribute(VertexAttribute::Usage::POSITION, 0, DataType::FLOAT_VECTOR3, false), // position
            VertexAttribute(VertexAttribute::Usage::COLOR, 0, DataType::UNSIGNED_BYTE_VECTOR4, true) // color
        };

        VertexPC::VertexPC()
        {
        }

        VertexPC::VertexPC(const Vector3& aPosition, Color aColor):
            position(aPosition), color(aColor)
        {
        }

        const std::vector<VertexAttribute> VertexPCT::ATTRIBUTES = {
            VertexAttribute(VertexAttribute::Usage::POSITION, 0, DataType::FLOAT_VECTOR3, false), // position
            VertexAttribute(VertexAttribute::Usage::COLOR, 0, DataType::UNSIGNED_BYTE_VECTOR4, true), // color
            VertexAttribute(VertexAttribute::Usage::TEXTURE_COORDINATES, 0, DataType::FLOAT_VECTOR2, false) // texcoord
        };

        VertexPCT::VertexPCT()
        {
        }

        VertexPCT::VertexPCT(const Vector3& aPosition, Color aColor, const Vector2& aTexCoord):
            position(aPosition), color(aColor), texCoord(aTexCoord)
        {
        }
    } // namespace graphics
} // namespace ouzel
