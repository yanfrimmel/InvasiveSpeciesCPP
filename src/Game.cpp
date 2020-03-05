#include "Game.h"

Game::Game(Configurations configurations)
{
  _graphics.reset(new Graphics(configurations.windowWidth, configurations.windowHeight, configurations.flags, configurations.fpsCap));
}

void Game::play()
{
    bool closeRequested = false;
    Uint32 startclock = 0;
    Uint32 deltaclock = 0;
    Uint32 currentFPS = 0;
    int mouseX, mouseY, buttons;
    int frameRateDelay = 1000.0f / _graphics->getFpsCap();

    while (!closeRequested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                closeRequested = 1;
                printf("closeRequested! quiting\n");
            }
        }

        buttons = SDL_GetMouseState(&mouseX, &mouseY);

        _graphics->fpsCounterLoop(&startclock, &deltaclock, &currentFPS);
        if ((_graphics->getFpsCap()) < currentFPS)
        {
            SDL_Delay((frameRateDelay)-deltaclock);
        }
        startclock = SDL_GetTicks();
    }
    _graphics.reset(nullptr);
}

Game::~Game()
{
    printf("Game destructor\n");
}
