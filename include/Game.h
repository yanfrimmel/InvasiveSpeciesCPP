#ifndef GAME_H /* Include guard */
#define GAME_H

#include "Graphics.h"

class Game
{
private:
    int _flags;
    unsigned short int _windowWidth;
    unsigned short int _windowHeight;
    std::unique_ptr<Graphics> _graphics;

public:
    Game(unsigned short int windowWidth = 800, unsigned short int windowHeight = 600, int flags = 0);
    void play();
    ~Game();
};

#endif