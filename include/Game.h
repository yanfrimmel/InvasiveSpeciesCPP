#ifndef GAME_H /* Include guard */
#define GAME_H

#include "FPSCounter.h"
#include "GameState.h"
#include "Graphics.h"

class Game {
private:
	std::unique_ptr<Graphics> _graphics;
	std::unique_ptr<GameState> _gameState;
	std::unique_ptr<MouseInput> _mouseInput;
	std::unique_ptr<FPSCounter> _fpsCounter;
	Uint32 _worldWidth;
	Uint32 _worldHeight;
	Uint32 _fpsCap;
	std::vector<GameObject> _map;

	auto gameLoop(Uint32 fpsCap = 60) -> void;
	auto handleMouseState(float fps) -> void;
	auto static checkForSDLQuitEvents() -> bool;
	auto convertStateToGraphicsMap()
		->std::vector<std::pair<TileType, SDL_Point>>;
	auto validatePlayerPosition() -> void;
	auto loadMap(const char *filename) -> void;

public:
	Game(Configurations configurations);
	auto start() -> void;
	~Game();
};

#endif
