#include "GameObject.h"

Uint32 GameObject::_idGenerator = 0;

GameObject::GameObject(Uint32 size, Uint32 speed, SDL_Point position, TileType tileType)
	: _size(size), _speed(speed), _position{(float)position.x, (float)position.y}, _tileType(tileType)
{
	_id = _idGenerator++; // TODO: load last value from file
}

auto GameObject::setPosition(SDL_Point position) -> void
{
	_position.x = position.x;
	_position.y = position.y;
}

auto GameObject::getPosition() -> SDL_Point
{
	return SDL_Point{(int)_position.x, (int)_position.y};
}

auto GameObject::getTileType() -> TileType
{
	return _tileType;
}

auto GameObject::onDestinationSelected(SDL_Point point, float fps) -> void {
    float proximityThreshold = _size / 2.F;
	float elapsed = 1 / fps;
    auto selectedPosition = Vector2d<float>(point.x, point.y);
    auto currPos = Vector2d<float>(_position.x, _position.y);
	float distanceBetweenPoints = Vector2d<float>::distance(currPos, selectedPosition);
    auto direction = Vector2d<float>::normal(selectedPosition - currPos);
    std::cout << "direction: (" << direction.x << ", " << direction.y << ")\n" ;
    auto newPosition = currPos + (direction * (_speed * elapsed));
	if (distanceBetweenPoints > proximityThreshold) {
        std::cout << "x: " << newPosition.x << " y: " << newPosition.y << " \n";
		_position.x = newPosition.x;
		_position.y = newPosition.y;
	}
}

GameObject::~GameObject()
{
    std::cout << "GameObject: "<< _id << ", destructor\n";
}
