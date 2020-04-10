#include "Animal.h"

Animal::Animal(Uint32 size, Uint32 speed, Vector2d<float> position, TileType tileType) 
	: GameObject(size, speed, position, tileType)
{

}

Animal::~Animal()
{
}
