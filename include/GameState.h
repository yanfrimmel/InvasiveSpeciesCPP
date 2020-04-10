#ifndef GAMESTATE_H /* Include guard */
#define GAMESTATE_H

#include "GameObject.h"

class GameState {
private:
	Vector2d<float> _camera;
	GameObject *_player;
	std::vector<GameObject> _gameObjects;
	auto initCameraPosition(unsigned short int windowWidth, unsigned short int windowHeight) -> void;

public:
	GameState(unsigned short int windowWidth, unsigned short int windowHeight);
	auto getCamera()->Vector2d<float>;
	auto setCamera(Vector2d<float> camera) -> void;
	auto getPlayer()->GameObject *;
	auto getGameObjects()->std::vector<GameObject> &;
	~GameState();
};

#endif
