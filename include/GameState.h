#ifndef GAMESTATE_H /* Include guard */
#define GAMESTATE_H

#include "GameObject.h"

class GameState
{
private:
	SDL_Point _camera;
	GameObject* _player;
	std::vector<GameObject> _gameObjects;
public:
	GameState();
	SDL_Point getCamera();
	void setCamera(SDL_Point camera);
	GameObject* getPlayer();
	std::vector<GameObject> getGameObjects();
	~GameState();
};

#endif
