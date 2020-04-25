#include "GameObject.h"

Uint32 GameObject::_idGenerator = 0;

GameObject::GameObject(Uint32 size, Uint32 speed, Vector2d<float> position, TileType tileType)
	: _size(size), _speed(speed), _position{ position }, _tileType(tileType) {
	_id = _idGenerator++; // TODO: load last value from file
}

auto GameObject::setPosition(Vector2d<float> position) -> void {
	_position = position;
}

auto GameObject::getPosition() -> Vector2d<float> & { return _position; }

auto GameObject::getTileType() -> TileType { return _tileType; }

auto GameObject::getSize() -> Uint32 { return _size; }

auto GameObject::getId() -> Uint32
{
	return _id;
}

auto GameObject::onDestinationSelected(Vector2d<int> selectedPosition, float fps) -> void {
	if (!isReachedDestination(selectedPosition)) {
		float elapsed = 1 / fps;
		auto direction = Vector2d<float>::normal((Vector2d<float>)selectedPosition - _position);
		auto newPosition = _position + ((Vector2d<float>)direction * (float)_speed * elapsed);
		_position = newPosition;
	}
}

auto GameObject::isReachedDestination(Vector2d<int> destination) -> bool
{
	int distanceBetweenPoints = Vector2d<int>::distance(_position, destination);
	int proximityThreshold = _size / 2;
	return distanceBetweenPoints <= proximityThreshold;
}

auto GameObject::setAsPlayer() -> void
{
	_isPlayer = true;
}

auto GameObject::validatePosition() -> void {
	if (_position.x < 0) {
		_position.x = 0;
	}
	if (_position.y < 0) {
		_position.y = 0;
	}
	if (_position.x >(float)globalParams::worldWidth) {
		_position.x = (float)globalParams::worldWidth;
	}
	if (_position.y >(float)globalParams::worldHeight) {
		_position.y = (float)globalParams::worldHeight;
	}
}

GameObject::~GameObject() {
	//    std::cout << "GameObject: "<< _id << ", destructor\n";
}
