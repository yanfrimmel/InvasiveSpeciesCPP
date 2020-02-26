#include "Game.h"
#include "Graphics.h"

Game::Game(unsigned short int windowWidth, unsigned short int windowHeight, int flags)
{
    Graphics *graphics = new Graphics(windowWidth, windowHeight, flags);
}

void Game::play() const
{
}