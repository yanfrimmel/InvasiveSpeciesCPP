#ifndef GAME_H /* Include guard */
#define GAME_H

#include "Graphics.h"
#include "Utils.h"

class Game
{
private:
    int _fps;
    int _flags;
    unsigned short int _windowWidth;
    unsigned short int _windowHeight;
    std::unique_ptr<Graphics> _graphics;

public:
    Game(Configurations configurations);
    void play();
    ~Game();
};

#endif
