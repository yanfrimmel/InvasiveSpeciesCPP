#include <cstdlib>
#include "Game.h"

int main(int argc, char *argv[])
{
    unsigned short int windowWidth = 800;
    unsigned short int windowHeight = 600;
    Uint32 flags = 0;
    unsigned short int fpsCap = 600;
    if (argc == 5) {
        windowWidth = atoi(argv[1]);
        windowHeight = atoi(argv[2]);
        flags = atoi(argv[3]);
        fpsCap = atoi(argv[4]);
    }
    std::unique_ptr<Game> game (new Game(Configurations{windowWidth, windowHeight, flags, fpsCap}));
    return 0;
}
