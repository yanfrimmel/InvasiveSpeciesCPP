#pragma once

#include "Common.h"
#include "Vector2d.h"

#define DEFAULT_OBJECT_SIZE 32

class GameObject {
private: 
	static Uint32 _idGenerator;
protected:
	Uint32 _id;
	Uint32 _size;
	Uint32 _speed;
	Vector2d<float> _position;
	TileType _tileType;
	
public:
	GameObject(Uint32 size, Uint32 speed, Vector2d<float> position,
		TileType tileType);
	auto setPosition(Vector2d<float> position) -> void;
	auto getPosition()->Vector2d<float> &;
	auto getTileType()->TileType;
	auto getSize()->Uint32;
	auto onDestinationSelected(Vector2d<int> point, float fps) -> void;
	auto isReachedDestination(Vector2d<float> destination) -> bool;
	virtual ~GameObject();
};
