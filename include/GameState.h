#ifndef GAMESTATE_H /* Include guard */
#define GAMESTATE_H

#include "GameObject.h"

class GameState
{
private:
	Vector2d<float> _camera;
	GameObject* _player;
	std::vector<GameObject> _gameObjects;
public:
	GameState();
    auto getCamera() -> Vector2d<float>;
    auto setCamera(Vector2d<float> camera) -> void;
    auto getPlayer() -> GameObject*;
    auto getGameObjects() -> std::vector<GameObject> ;
	~GameState();
};

#endif
