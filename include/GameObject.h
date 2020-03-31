#ifndef GAMEOBJECT_H /* Include guard */
#define GAMEOBJECT_H

#include "Common.h"
#include "Vector2d.h"

class GameObject
{
private:
	Uint32 _id;
	Uint32 _size;
	Uint32 _speed;
	Vector2d<float> _position;
	TileType _tileType;
	static Uint32 _idGenerator;

public:
	GameObject(Uint32 size, Uint32 speed, SDL_Point position, TileType tileType);
	void setPosition(SDL_Point position);
	SDL_Point getPosition();
	TileType getTileType();
	void onDestinationSelected(SDL_Point point, float fps);
	~GameObject();
};

#endif
