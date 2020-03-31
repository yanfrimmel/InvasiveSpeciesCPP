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
    _gameState.reset(new GameState()); //TODO: initail game state
    _mouseInput.reset(new MouseInput { -1, -1, 0});
    _fpsCounter.reset(new FPSCounter());
    _fpsCounter->fpsInit();

    gameLoop(configurations.fpsCap, 1000.0f / configurations.fpsCap);
}

std::map<TileType, std::vector<SDL_Point>> Game::convertStateToGraphicsMap()
{
    return [this]() -> std::map<TileType, std::vector<SDL_Point>>
    {
        return std::map<TileType, std::vector<SDL_Point>>{
            {   _gameState->getPlayer()->getTileType(), {_gameState->getPlayer()->getPosition()}}
        };
    }();
}

bool Game::checkForSDLQuitEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            printf("closeRequested! quiting\n");
            return true;
        }
    }
    return false;
}

void Game::handleMouseState(float fps)
{
    _mouseInput.get()->mouseState = SDL_GetMouseState(&_mouseInput.get()->mouseX, &_mouseInput.get()->mouseY);
    if (_mouseInput->mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        // printf("SDL_MOUSEBUTTONDOWN\n");
        _gameState->getPlayer()->onDestinationSelected(SDL_Point {_mouseInput ->mouseX, _mouseInput->mouseY}, fps);
        //TODO: on mouse click
    }
}

void Game::gameLoop(Uint32 fpsCap, float minFrameRateDelay)
{
    while (true)
    {
        // process events
        if(checkForSDLQuitEvents()) return;

        _graphics->clearRender();
        float averageFPS = _fpsCounter->getAverageFramesPerSecond();
        handleMouseState(averageFPS);
        _graphics->renderGrid(convertStateToGraphicsMap());
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
