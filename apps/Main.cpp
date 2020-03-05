#include <cstdlib>
#include "Game.h"

int main(int argc, char *argv[])
{
    unsigned short int windowWidth = 800;
    unsigned short int windowHeight = 600;
    int flags = 0;
    unsigned short int fpsCap = 2000;
    if (argc == 4) {
        windowWidth = atoi(argv[1]);
        windowHeight = atoi(argv[2]);
        flags = atoi(argv[3]);
    }
    std::unique_ptr<Game> game (new Game(Configurations{windowWidth, windowHeight, flags, fpsCap}));
    game->play();

    return 0;
}
