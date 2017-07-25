// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "BufferResource.h"

namespace ouzel
{
    namespace graphics
    {
        BufferResource::BufferResource()
        {
        }

        BufferResource::~BufferResource()
        {
        }

        bool BufferResource::init(Buffer::Usage newUsage, bool newDynamic)
        {
            usage = newUsage;
            dynamic = newDynamic;

            return true;
        }

        bool BufferResource::init(Buffer::Usage newUsage, const std::vector<uint8_t>& newData, bool newDynamic)
        {
            usage = newUsage;
            dynamic = newDynamic;
            data = newData;

            return true;
        }

        bool BufferResource::setData(const std::vector<uint8_t>& newData)
        {
            if (!dynamic)
            {
                return false;
            }

            data = newData;

            return true;
        }
    } // namespace graphics
} // namespace ouzel
