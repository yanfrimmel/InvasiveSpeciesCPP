#include "GameState.h"

GameState::GameState()
{
	_camera = {0,0};
    _gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 100 ,{400, 400}, HUMAN_MALE));
	_player = &_gameObjects[0];
}

auto GameState::getCamera() -> Vector2d<float>
{
	return _camera;
}

auto GameState::setCamera(Vector2d<float> camera) -> void
{
	_camera = camera;
}

auto GameState::getPlayer() -> GameObject*
{
	return _player;
}

auto GameState::getGameObjects() -> std::vector<GameObject>
{
	return _gameObjects;
}

GameState::~GameState()
{
    std::cout << "GameState destructor\n";
	_player = nullptr;
	_gameObjects.clear();
	_gameObjects.shrink_to_fit();
}
