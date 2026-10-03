#include "Engine.h"

#include <cstdlib>

auto main() -> int
{
    engine::Engine gameEngine;

    if (!gameEngine.init())
    {
        return EXIT_FAILURE;
    }

    while (gameEngine.isRunning())
    {
        gameEngine.update();
    }

    gameEngine.shutdown();

    return EXIT_SUCCESS;
}
