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
    _gameState.reset(new GameState {}); //TODO: initail game state
    _mouseInput.reset(new MouseInput { -1, -1, 0});
    _fpsCounter.reset(new FPSCounter());
    _fpsCounter->fpsInit();

    gameLoop(configurations.fpsCap, 1000.0f / configurations.fpsCap);
}
//TODO: Draw grid & inital game state
void Game::gameLoop(Uint32 fpsCap, float minFrameRateDelay)
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
        float averageFPS = _fpsCounter->getAverageFramesPerSecond();

        _graphics->clearRender();
        _graphics->renderGrid(nullptr);
        _graphics->renderText("FPS: " + std::to_string(averageFPS), {255, 255, 0, 255}, 0, 0);
        _graphics->presentRender();
        if (fpsCap < averageFPS)
        {
            SDL_Delay(minFrameRateDelay);
        }
        _fpsCounter->fpsThink();
    }
}

Game::~Game()
{
    printf("Game destructor\n");
}
