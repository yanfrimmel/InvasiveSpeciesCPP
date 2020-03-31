#include "GameState.h"

GameState::GameState()
{
	_camera = {0,0};
	_gameObjects.push_back(GameObject(32, 100 ,{400, 400}, HUMAN_MALE));
	_player = &_gameObjects[0];
}

SDL_Point GameState::getCamera()
{
	return _camera;
}

void GameState::setCamera(SDL_Point camera)
{
	_camera = camera;
}

GameObject* GameState::getPlayer()
{
	return _player;
}

std::vector<GameObject> GameState::getGameObjects()
{
	return _gameObjects;
}

GameState::~GameState()
{
	printf("GameState destructor\n");
	_player = nullptr;
	_gameObjects.clear();
	_gameObjects.shrink_to_fit();
}