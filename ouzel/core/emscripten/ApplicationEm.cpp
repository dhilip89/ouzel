// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include <emscripten.h>
#include "ApplicationEm.h"
#include "core/Engine.h"
#include "utils/Utils.h"

static void loop(void)
{
    if (ouzel::sharedEngine->isActive())
    {
        static_cast<ouzel::ApplicationEm*>(ouzel::sharedApplication)->step();
    }
    else
    {
        emscripten_cancel_main_loop();
    }
}

namespace ouzel
{
    ApplicationEm::ApplicationEm(int pArgc, char* pArgv[]):
        Application(pArgc, pArgv)
    {
    }

    int ApplicationEm::run()
    {
        ouzelMain(args);

        if (!sharedEngine)
        {
            return 1;
        }

        sharedEngine->begin();

        emscripten_set_main_loop(loop, 1, 1);

        sharedEngine->end();

        return 0;
    }

    void ApplicationEm::step()
    {
        executeAll();

        if (!sharedEngine->draw())
        {
            sharedEngine->exit();
        }
    }
}