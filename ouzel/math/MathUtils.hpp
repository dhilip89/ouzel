// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cstdint>
#include "math/Vector2.hpp"
#include "math/Size2.hpp"

namespace ouzel
{
    const float TAU = 6.28318530717958647692f;
    const float TAU_2 = 3.14159265358979323846f; // tau/2, the same as pi
    const float TAU_4 = 1.57079632679489661923f; // tau/4, the same as pi/2
    const float PI = 3.14159265358979323846f;
    const float PI_2 = 1.57079632679489661923f; // pi/2
    const float PI_4 = 0.78539816339744830962f; // pi/4
    const float FLOAT_SMALL = 1.0e-37f;
    const float TOLERANCE = 2e-37f;
    const float E = 2.71828182845904523536f;
    const float LOG10E = 0.4342944819032518f;
    const float LOG2E = 1.442695040888963387f;
    const float PIX2 = 6.28318530717958647693f;
    const float EPSILON = 0.000001f;
    const float SQRT2 = 1.4142135623730950488f;

    inline float lerp(float v0, float v1, float t)
    {
        return (1.0f - t) * v0 + t * v1;
    }

    inline float smoothStep(float a, float b, float t)
    {
        float remapSmoothStep = t * t * (3 - 2 * t);
        return lerp(a, b, remapSmoothStep);
    }

    inline bool isPOT(uint32_t x)
    {
        return (x != 0) && (((x - 1) & x) == 0);
    }

    inline int nextPOT(int x)
    {
        x = x - 1;
        x = x | (x >> 1);
        x = x | (x >> 2);
        x = x | (x >> 4);
        x = x | (x >> 8);
        x = x | (x >>16);
        return x + 1;
    }

    template<typename T> inline int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    inline float degToRad(float x)
    {
        return x * 0.0174532925f;
    }

    inline float radToDeg(float x)
    {
        return x * 57.29577951f;
    }

    template<class T>
    inline T clamp(T x, T lo, T hi)
    {
        return (x < lo) ? lo : ((x > hi) ? hi : x);
    }

    static const uint64_t INITIAL_FNV = 2166136261U;
    static const uint64_t FNV_MULTIPLE = 16777619;

    // Fowler / Noll / Vo (FNV) hash
    inline uint64_t fnvHash(uint64_t s)
    {
        uint64_t hash = INITIAL_FNV;
        for (uint64_t i = 0; i < sizeof(uint64_t); i++)
        {
            hash = hash ^ (reinterpret_cast<uint8_t*>(&s)[i]); // xor the low 8 bits
            hash = hash * FNV_MULTIPLE; // multiply by the magic number
        }
        return hash;
    }
}
