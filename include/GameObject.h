#ifndef GAMEOBJECT_H /* Include guard */
#define GAMEOBJECT_H

#include "Common.h"
#include "Vector2d.h"

#define DEFAULT_OBJECT_SIZE 32

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
    auto setPosition(SDL_Point position) -> void;
    auto getPosition() -> SDL_Point;
    auto getTileType() -> TileType;
    auto onDestinationSelected(SDL_Point point, float fps) -> void;
	~GameObject();
};

#endif
