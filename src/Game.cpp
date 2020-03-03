#include "Game.h"
#include "Graphics.h"

Game::Game(unsigned short int windowWidth, unsigned short int windowHeight, int flags)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _flags = flags;
}

void Game::play()
{
    _graphics.reset(new Graphics(_windowWidth, _windowHeight, _flags));
    bool closeRequested = false;
        while (!closeRequested) {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                closeRequested = 1;
                printf("closeRequested! quiting\n");
            }
        }
    }
}

Game::~Game() 
{ 
    printf("Game destructor\n");
} 