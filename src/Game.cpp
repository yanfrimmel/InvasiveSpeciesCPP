#include "Game.h"

Game::Game(Configurations configurations) {
	_graphics = std::make_unique<Graphics>(configurations.windowWidth,
		configurations.windowHeight,
		configurations.flags);
	_gameState = std::make_unique<GameState>(configurations.windowWidth,
		configurations.windowHeight);
	_mouseInput = std::make_unique<MouseInput>(MouseInput{ -1, -1, 0 });
	_fpsCounter = std::make_unique<FPSCounter>();
	globalParams::worldWidth = configurations.worldWidth;
	globalParams::worldHeight = configurations.worldHeight;
	_fpsCap = configurations.fpsCap;
}

auto Game::start() -> void {
	_fpsCounter->fpsInit();
	gameLoop(_fpsCap);
}

auto Game::convertStateToGraphicsMap() -> std::vector<std::pair<TileType, SDL_Rect>> {
	std::vector<std::pair<TileType, SDL_Rect>> convertedVector;

	for (auto& o : _gameState->getGameObjects()) {
		convertedVector.push_back(
			std::make_pair(o->getTileType(), SDL_Rect{ (int)o->getPosition().x,
													  (int)o->getPosition().y,
													  (int)o->getSize(),
													  (int)o->getSize() }));
	}

	auto end = std::remove_if(convertedVector.begin(), convertedVector.end(),
		[this](std::pair<TileType, SDL_Rect> o) {
		return o.second.x - _gameState->getCamera().x < - o.second.w || // left
			o.second.y - _gameState->getCamera().y < - o.second.h || // right
			o.second.x - _gameState->getCamera().x >(int)_graphics->getWindowWidth() || // right
			o.second.y - _gameState->getCamera().y >(int)_graphics->getWindowHeight(); // down
	});

	convertedVector.erase(end, convertedVector.end());

	for (auto &o : convertedVector) {
		o.second.x -= (int)_gameState->getCamera().x;
		o.second.y -= (int)_gameState->getCamera().y;
	}
	return convertedVector;
}

auto Game::checkForSDLQuitEvents() -> bool {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			std::cout << "SDL_QUIT requested! quiting\n";
			return true;
		}
	}
	return false;
}

auto Game::handleMouseState(float fps) -> void {
	_mouseInput->mouseState =
		SDL_GetMouseState(&_mouseInput->mouseX, &_mouseInput->mouseY);
	if (_mouseInput->mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		// printf("SDL_MOUSEBUTTONDOWN\n");
		auto halfWindowWidth = _graphics->getWindowWidth() / 2;
		auto halfWindowHeight = _graphics->getWindowHeight() / 2;
		_gameState->setCamera(
		{ _gameState->getPlayer().getPosition().x - halfWindowWidth, _gameState->getPlayer().getPosition().y - halfWindowHeight });
		_gameState->getPlayer().onDestinationSelected(
       { _mouseInput->mouseX + (int)_gameState->getCamera().x, _mouseInput->mouseY + (int)_gameState->getCamera().y }, fps);
		_gameState->getPlayer().validatePosition();
	}
}

auto Game::gameLoop(Uint32 fpsCap) -> void {
	float minFrameRateDelay = MILLISECOND_IN_SECOND / fpsCap;
	while (true) {
		// process events
		if (checkForSDLQuitEvents())
			return;

		_graphics->clearRender();
		float averageFPS = _fpsCounter->getAverageFramesPerSecond();
		handleMouseState(averageFPS);
		_gameState->updateGameObjects(averageFPS);
		_graphics->renderGrid(convertStateToGraphicsMap());
		_graphics->renderText("FPS: " + std::to_string((int)averageFPS), { 255, 255, 0, 255 }, 0, 0);
		_graphics->presentRender();

		if (fpsCap < averageFPS) {
			SDL_Delay((Uint32)minFrameRateDelay);
		}
		_fpsCounter->fpsThink();
	}
}

auto Game::loadMap(const char *filename) -> void {
	/*int current, mx, my, mw, mh;
	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cout << "Failed to open map file." << std::endl;
		return;
	}
	in >> mw;
	in >> mh;
	in >> mx;
	in >> my;
	for (int i = 0; i < mh; i++) {
		for (int j = 0; j < mw; j++) {
			if (in.eof()) {
				std::cout << "Reached end of map file too soon." << std::endl;
				return;
			}
			in >> current;
			if (current != 0) {
				GameObject tmp(DEFAULT_OBJECT_SIZE, 0, { 0, 0 }, HUMAN_FEMALE);
				if (current == 2 || current == 4) {
				}
				_map.push_back(tmp);
			}
		}
	}
	in.close();*/
}

Game::~Game() { std::cout << "Game destructor" << std::endl; }
