#include "Game.h"

Game::Game(Configurations configurations)
{
    start(configurations);
}

auto Game::start(Configurations configurations) -> void
{
    _graphics = std::make_unique<Graphics>(
                        configurations.windowWidth,
                        configurations.windowHeight,
                        configurations.flags);
    _gameState = std::make_unique<GameState>(); //TODO: initail game state
    _mouseInput = std::make_unique<MouseInput>(MouseInput { -1, -1, 0});
    _fpsCounter = std::make_unique<FPSCounter>();
    _fpsCounter->fpsInit();

    gameLoop(configurations.fpsCap, MILLISECOND_IN_SECOND / configurations.fpsCap);
}

auto Game::convertStateToGraphicsMap() -> std::map<TileType, std::vector<SDL_Point>>
{
    return [this]() -> std::map<TileType, std::vector<SDL_Point>>
    {
        return std::map<TileType, std::vector<SDL_Point>>{
            {   _gameState->getPlayer()->getTileType(), {_gameState->getPlayer()->getPosition()}}
        };
    }();
}

auto Game::checkForSDLQuitEvents() -> bool
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            std::cout << "closeRequested! quiting\n";
            return true;
        }
    }
    return false;
}

auto Game::handleMouseState(float fps) -> void
{
    _mouseInput->mouseState = SDL_GetMouseState(&_mouseInput->mouseX, &_mouseInput->mouseY);
    if (_mouseInput->mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        // printf("SDL_MOUSEBUTTONDOWN\n");
        _gameState->getPlayer()->onDestinationSelected(SDL_Point {_mouseInput ->mouseX, _mouseInput->mouseY}, fps);
        //TODO: on mouse click
    }
}

auto Game::gameLoop(Uint32 fpsCap, float minFrameRateDelay) -> void
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
    std::cout << "Game destructor\n";
}
