#include "Game.h"

Game::Game(Configurations configurations)
{
    start(configurations);
}

void Game::start(Configurations configurations)
{
    _graphics.reset(new Graphics(
                        configurations.windowWidth,
                        configurations.windowHeight,
                        configurations.flags));
    // _gameState.reset(new GameState {}); //TODO: initail game state
    _mouseInput.reset(new MouseInput { -1, -1, 0});
    Uint32 sdlInitTicks = SDL_GetTicks();
    gameLoop(configurations.fpsCap, 1000.0f / configurations.fpsCap, sdlInitTicks, sdlInitTicks);
}
//TODO: Draw grid & inital game state
void Game::gameLoop(Uint32 fpsCap, Uint32 frameRateDelay, Uint32 startClock, Uint32 deltaClock)
{
    while (true)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("closeRequested! quiting\n");
                return;
            case SDL_MOUSEBUTTONDOWN:
                break;
            }
        }

        _mouseInput.get()->mouseState = SDL_GetMouseState(&_mouseInput.get()->mouseX, &_mouseInput.get()->mouseY);
        if (_mouseInput.get()->mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            //TODO: on mouse click
        }
        Uint32 currentFPS = _graphics.get()->calculateFpsAndDelta(&startClock, &deltaClock);

        if ((fpsCap) < currentFPS)
        {
            SDL_Delay(frameRateDelay - deltaClock);
        }

        deltaClock = SDL_GetTicks() - startClock;
        startClock = SDL_GetTicks();
    }
}

Game::~Game()
{
    printf("Game destructor\n");
}
