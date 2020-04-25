#include "GameState.h"

GameState::GameState(unsigned short int windowWidth, unsigned short int windowHeight)
{
	//TODO: init positions from a map file
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 500, 900 }, CHICKEN_FEMALE));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 464, 900 }, CHICKEN_MALE));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 700, 800 }, WATER));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 732, 800 }, WATER));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 660 , 1600 }, STONE));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1700 , 700 }, GRASS));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1700 , 732 }, GRASS));
	//_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1732 , 700 }, GRASS));
	_gameObjects.emplace_back(new Grass({ 700 , 650 }));
	_gameObjects.emplace_back(new Grass({ 550 , 500 }));
	_gameObjects.emplace_back(new Human(Animal::male, { 400, 600 }));
	_gameObjects.emplace_back(new Human(Animal::female, { 600, 700 }));
	_player = _gameObjects.back().get();
	_player->setAsPlayer();

	initCameraPosition(windowWidth, windowHeight);
}

auto GameState::initCameraPosition(unsigned short int windowWidth, unsigned short int windowHeight) -> void {
	_camera = { (_player->getPosition().x - windowWidth / 2), (_player->getPosition().y - windowHeight / 2) };
}

auto GameState::getCamera() -> Vector2d<float> { return _camera; }

auto GameState::setCamera(Vector2d<float> camera) -> void { _camera = camera; }

auto GameState::getPlayer() -> GameObject& { return *_player; }

auto GameState::getGameObjects() ->std::vector<std::unique_ptr<GameObject>>& {
	return _gameObjects;
}

auto GameState::updateGameObjects(float fps) -> void
{
	if (fps <= 0) return;
	for (unsigned int i = 0; i < _gameObjects.size(); i++) {
		auto & gameObjecet = _gameObjects[i];
		if ((gameObjecet.get())) {
			gameObjecet.get()->act(_gameObjects, fps);
		}
	}
}

GameState::~GameState() {
	std::cout << "GameState destructor\n";
	_gameObjects.clear();
	_gameObjects.shrink_to_fit();
}
