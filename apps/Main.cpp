#include "Game.h"

const int MAX_VALID_ARGC_NUMBER = 5;
const Uint32 DEFAULT_WINDOW_WIDTH = 800;
const Uint32 DEFAULT_WINDOW_HEIGHT = 600;
const Uint32 DEFAULT_WORLD_WIDTH = 2000;
const Uint32 DEFAULT_WORLD_HEIGHT = 2000;
const Uint32 DEFAULT_FLAGS = 0;
const Uint32 DEFAULT_FPS_CAP = 1000;

auto argvValidator(const std::string& arg, Uint32& cleanValue) -> bool
{
    try {
      std::size_t pos;
      cleanValue = std::stoi(arg, &pos);
      if (pos < arg.size()) {
        std::cerr << "Trailing characters after number: " << arg << '\n';
      }
    } catch (std::invalid_argument const &ex) {
      std::cerr << "Invalid number: " << arg << '\n';
      return false;
    } catch (std::out_of_range const &ex) {
      std::cerr << "Number out of range: " << arg << '\n';
      return false;
    }
    return true;
}

auto main(int argc, char *argv[]) -> int
{
    std::queue<Uint32*> argsQueue;
    Uint32 windowWidth = DEFAULT_WINDOW_WIDTH;
    Uint32 windowHeight = DEFAULT_WINDOW_HEIGHT;
    Uint32 worldWidth = DEFAULT_WORLD_WIDTH;
    Uint32 worldHeight = DEFAULT_WORLD_HEIGHT;
    Uint32 flags = DEFAULT_FLAGS;
    Uint32 fpsCap = DEFAULT_FPS_CAP;
    argsQueue.push(&windowWidth);
    argsQueue.push(&windowHeight);
    argsQueue.push(&worldWidth);
    argsQueue.push(&worldHeight);
    argsQueue.push(&flags);
    argsQueue.push(&fpsCap);

    if (argc <= MAX_VALID_ARGC_NUMBER)
    {
        std::vector<std::string> args( argv, argv + argc ); //do not use pointer arithmetic
        for (int i = 1; i < argc; ++i)
        {
            if (!argvValidator(args[i], *argsQueue.front()))
            {
                 return 1;
            }
            argsQueue.pop();
        }
     }
    else {
        std::cerr << "Invalid number of arguments: " << argc << '\n';
        return 1;
    }

    std::unique_ptr<Game> game (new Game(Configurations{windowWidth, windowHeight, flags, fpsCap, worldWidth, worldHeight}));
    game->start();
    return 0;
}
