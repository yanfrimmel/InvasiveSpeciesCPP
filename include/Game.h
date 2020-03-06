#ifndef GAME_H /* Include guard */
#define GAME_H

#include "Graphics.h"

class Game
{
private:
	std::unique_ptr<Graphics> _graphics;
	std::unique_ptr<GameState> _gameState;
	std::unique_ptr<MouseInput> _mouseInput;

	void start(Configurations configurations);
	void gameLoop(Uint32 fpsCap = 60, Uint32 frameRateDelay = 1000, Uint32 startClock = 0, Uint32 deltaClock = 0);

public:
	Game(Configurations configurations);
	~Game();
};

#endif
