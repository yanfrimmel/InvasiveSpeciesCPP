#include "GameState.h"

GameState::GameState(unsigned short int windowWidth, unsigned short int windowHeight) {
	//TODO: init positions from a map file
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 500, 900 }, CHICKEN_FEMALE));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 464, 900 }, CHICKEN_MALE));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 700, 800 }, WATER));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 732, 800 }, WATER));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 660 , 1600 }, STONE));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1700 , 700 }, GRASS));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1700 , 732 }, GRASS));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1732 , 700 }, GRASS));
	_gameObjects.emplace_back(new GameObject(DEFAULT_OBJECT_SIZE, 200, { 1732 , 732 }, GRASS));
	_gameObjects.emplace_back(new Human(Animal::male, { 400, 600 }));

	_gameObjects.emplace_back(new Human(Animal::female, { 600, 700 }));
	initCameraPosition(windowWidth, windowHeight);
}

auto GameState::initCameraPosition(unsigned short int windowWidth, unsigned short int windowHeight) -> void {
	_camera = { (getPlayer()->getPosition().x - windowWidth / 2), (getPlayer()->getPosition().y - windowHeight / 2) };
}

auto GameState::getCamera() -> Vector2d<float> { return _camera; }

auto GameState::setCamera(Vector2d<float> camera) -> void { _camera = camera; }

auto GameState::getPlayer() -> std::unique_ptr<GameObject>& { return  _gameObjects.at(_gameObjects.size() - 1); }

auto GameState::getGameObjects() ->std::vector<std::unique_ptr<GameObject>>& {
	return _gameObjects;
}

auto GameState::updateGameObjects(float fps) -> void
{
	if (fps <= 0) return;
	for (unsigned int i = 0; i < _gameObjects.size(); i++) {
		auto & gameObjecet = _gameObjects[i];
		if (dynamic_cast<Animal*> (gameObjecet.get())) {
			Animal* animal = ((Animal*)gameObjecet.get());
			animal->think(_gameObjects, fps);
		}
	}
}

GameState::~GameState() {
	std::cout << "GameState destructor\n";
	_gameObjects.clear();
	_gameObjects.shrink_to_fit();
}
