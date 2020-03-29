#include "GameObject.h"

GameObject::GameObject(Uint32 id, Uint32 speed, SDL_Point position, TileType tileType) 
 : _id{id}, _speed{speed}, _position{position}, _tileType{tileType}
{}

void GameObject::setPosition(SDL_Point position)
{
	_position = position;
}

SDL_Point GameObject::getPosition()
{
	return _position;
}

TileType GameObject::getTileType()
{
	return _tileType;
}

GameObject::~GameObject()
{
    printf("GameObject: %d, destructor\n",_id);
}
