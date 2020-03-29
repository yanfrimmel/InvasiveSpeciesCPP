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

	void start(Configurations configurations);
	void gameLoop(Uint32 fpsCap = 60, float minFrameRateDelay = 1.0);
	std::map<TileType, std::vector<SDL_Point>> convertStateToGraphicsMap();

public:
	Game(Configurations configurations);
	~Game();
};

#endif
