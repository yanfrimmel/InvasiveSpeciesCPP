#pragma once
#include "GameObject.h"
class Animal :
	public GameObject
{
public:
	Animal(Uint32 size, Uint32 speed, Vector2d<float> position, TileType tileType);
	~Animal();
};

