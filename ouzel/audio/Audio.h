// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <set>
#include <vector>
#include "math/Vector3.h"
#include "utils/Types.h"

#ifdef OPENAL
#undef OPENAL
#endif

namespace ouzel
{
    class Engine;

    namespace audio
    {
        class Resource;
        
        class Audio
        {
            friend Engine;
        public:
            enum class Driver
            {
                DEFAULT,
                EMPTY,
                OPENAL,
                XAUDIO2,
                OPENSL
            };

            virtual ~Audio();

            virtual bool init();

            virtual bool process();

            virtual void setListenerPosition(const Vector3& newPosition);
            virtual void setListenerOrientation(const Vector3& newOrientation);

            virtual SoundPtr createSound() = 0;

            uint16_t getAPIMajorVersion() const { return apiMajorVersion; }
            uint16_t getAPIMinorVersion() const { return apiMinorVersion; }

            bool isReady() const { return ready; }

        protected:
            Audio(Driver aDriver);

            Driver driver;

            uint16_t apiMajorVersion = 0;
            uint16_t apiMinorVersion = 0;

            bool ready = false;

            Vector3 listenerPosition;
            Vector3 listenerOrientation;

            std::mutex resourceMutex;
            std::vector<std::unique_ptr<Resource>> resources;
            std::set<Resource*> resourceUploadSet;
            std::vector<std::unique_ptr<Resource>> resourceDeleteSet;
        };
    } // namespace audio
} // namespace ouzel
