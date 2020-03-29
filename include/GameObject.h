#ifndef GAMEOBJECT_H /* Include guard */
#define GAMEOBJECT_H

#include "Common.h"

class GameObject
{
private:
	Uint32 _id;
	Uint32 _speed;
	SDL_Point _position;
	TileType _tileType;

public:
	GameObject(Uint32 id, Uint32 speed, SDL_Point position, TileType tileType);
	void setPosition(SDL_Point position);
	SDL_Point getPosition();
	TileType getTileType();
	~GameObject();
};

#endif
