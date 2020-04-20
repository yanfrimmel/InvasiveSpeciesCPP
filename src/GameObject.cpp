#include "GameObject.h"

Uint32 GameObject::_idGenerator = 0;

GameObject::GameObject(Uint32 size, Uint32 speed, Vector2d<float> position,
	TileType tileType)
	: _size(size), _speed(speed), _position{ position }, _tileType(tileType) {
	_id = _idGenerator++; // TODO: load last value from file
}

auto GameObject::setPosition(Vector2d<float> position) -> void {
	_position = position;
}

auto GameObject::getPosition() -> Vector2d<float> & { return _position; }

auto GameObject::getTileType() -> TileType { return _tileType; }

auto GameObject::getSize() -> Uint32 { return _size; }

auto GameObject::onDestinationSelected(Vector2d<int> selectedPosition, float fps) -> void {
	if (!isReachedDestination(selectedPosition)) {
		if (fps == 0.0) return;
		float elapsed = 1 / fps;
		auto direction = Vector2d<float>::normal((Vector2d<float>)selectedPosition - _position);
		Vector2d<float> newPosition = _position + ((Vector2d<float>)direction * (float)_speed * elapsed);
		_position.x = newPosition.x;
		_position.y = newPosition.y;
	}
}

auto GameObject::isReachedDestination(Vector2d<float> destination) -> bool
{
	float distanceBetweenPoints = Vector2d<float>::distance(_position, destination);
	float proximityThreshold = _size / 2.F;
	return distanceBetweenPoints <= proximityThreshold;
}

GameObject::~GameObject() {
	//    std::cout << "GameObject: "<< _id << ", destructor\n";
}
