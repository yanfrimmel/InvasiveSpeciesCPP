#include "GameState.h"

GameState::GameState(unsigned short int windowWidth, unsigned short int windowHeight) {
	//TODO: init pistions from a map file
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 400, 450 }, HUMAN_FEMALE));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 500, 600 }, CHICKEN_FEMALE));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 464, 600 }, CHICKEN_MALE));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 700, 800 }, WATER));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 732, 800 }, WATER));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 660 , 600 }, STONE));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 700 , 700 }, GRASS));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 700 , 732 }, GRASS));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 732 , 700 }, GRASS));
	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 732 , 732 }, GRASS));

	_gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200, { 600, 600 }, HUMAN_MALE));
	_player = &_gameObjects.at(_gameObjects.size() - 1);
	initCameraPosition(windowWidth, windowHeight);
}

auto GameState::initCameraPosition(unsigned short int windowWidth, unsigned short int windowHeight) -> void {
	_camera = { _player->getPosition().x - windowWidth / 2, _player->getPosition().y - windowHeight / 2 };
}

auto GameState::getCamera() -> Vector2d<float> { return _camera; }

auto GameState::setCamera(Vector2d<float> camera) -> void { _camera = camera; }

auto GameState::getPlayer() -> GameObject * { return _player; }

auto GameState::getGameObjects() -> std::vector<GameObject>& {
	return _gameObjects;
}

GameState::~GameState() {
	std::cout << "GameState destructor\n";
	_gameObjects.clear();
	_gameObjects.shrink_to_fit();
}
