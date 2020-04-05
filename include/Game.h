#ifndef GAME_H /* Include guard */
#define GAME_H

#include "Graphics.h"
#include "FPSCounter.h"
#include "GameState.h"

class Game
{
private:
	std::unique_ptr<Graphics> _graphics;
	std::unique_ptr<GameState> _gameState;
	std::unique_ptr<MouseInput> _mouseInput;
	std::unique_ptr<FPSCounter> _fpsCounter;
    unsigned short int _worldWidth;
    unsigned short int _worldHeight;
    unsigned short int _fpsCap;

    auto gameLoop(float fpsCap = 60.F) -> void;
    auto handleMouseState(float fps) -> void;
    auto static checkForSDLQuitEvents() -> bool;
    auto convertStateToGraphicsMap() -> std::vector<std::pair<TileType, SDL_Point>>;
    auto validatePlayerPosition() -> void;

public:
    Game(Configurations configurations);
    auto start() -> void;
	~Game();
};

#endif
