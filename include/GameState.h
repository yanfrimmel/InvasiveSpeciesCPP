#pragma once

#include "GameObject.h"
#include "Human.h"
#include "Grass.h"
#include "Water.h"

class GameState {
private:
	GameObject* _player;
	Vector2d<float> _camera;
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
	auto initCameraPosition(unsigned short int windowWidth, unsigned short int windowHeight) -> void;
	
public:
	GameState(unsigned short int windowWidth, unsigned short int windowHeight);
	auto getCamera()->Vector2d<float>;
	auto setCamera(Vector2d<float> camera) -> void;
	auto getPlayer()->GameObject&;
	auto getGameObjects()->std::vector<std::unique_ptr<GameObject>>&;
	auto updateGameObjects(float fps) -> void;
	~GameState();
};