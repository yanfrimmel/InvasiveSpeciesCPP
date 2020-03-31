#include "GameObject.h"

Uint32 GameObject::_idGenerator = 0;

GameObject::GameObject(Uint32 size, Uint32 speed, SDL_Point position, TileType tileType)
	: _size(size), _speed(speed), _position{(float)position.x, (float)position.y}, _tileType(tileType)
{
	_id = _idGenerator++; // TODO: load last value from file
}

void GameObject::setPosition(SDL_Point position)
{
	_position.x = position.x;
	_position.y = position.y;
}

SDL_Point GameObject::getPosition()
{
	return SDL_Point{(int)_position.x, (int)_position.y};
}

TileType GameObject::getTileType()
{
	return _tileType;
}

void GameObject::onDestinationSelected(SDL_Point point, float fps) {
	float proximityThreshold = _size / 2;
	float elapsed = 1 / fps;
	Vector2d<float> mouseWorldPos = Vector2d<float>(point.x, point.y);
	Vector2d<float> currPos = Vector2d<float>(_position.x, _position.y);
	float distanceBetweenPoints = Vector2d<float>::distance(currPos, mouseWorldPos);
	Vector2d<float> direction = Vector2d<float>::normal(mouseWorldPos - currPos);
	printf("direction: (%f, %f) \n", direction.x, direction.y);
	Vector2d<float> newPosition = currPos + (direction * (_speed * elapsed));
	if (distanceBetweenPoints > proximityThreshold) {
		printf("x: %f y: %f \n", newPosition.x, newPosition.y);
		_position.x = newPosition.x;
		_position.y = newPosition.y;
	}
//    inputEventHandler :: Inputs -> GameState -> GameState  --TODO handle world camera
	// inputEventHandler i g =
	//   if isLeftButtonDown (fst $ _mouseInput i) &&
	//     distanceBetweenPoints > proximityThreshold
	//     then
	//       updatePlayerPosition (fromPointDoubleToPointCInt $ P newPositon) g
	//   else
	//     g
	//   where
//    mouseWorldPos = getMousePosition (snd $ _mouseInput i) ^+^ _camera g
//    speed = _speed (_player g)
//    currPos = _position (_player g)
//    elapsed = 1 / fromIntegral (_currentFPS i)
//    direction = normalize $ fromPointCIntToVectorDouble mouseWorldPos ^-^ fromPointCIntToVectorDouble currPos
//    newPositon = fromPointCIntToVectorDouble currPos ^+^ (direction ^* (fromIntegral speed * elapsed))
//    distanceBetweenPoints = distance (fromPointCIntToVectorDouble currPos) (fromPointCIntToVectorDouble mouseWorldPos)
//    proximityThreshold = fromIntegral textureDimensions / 8
}

GameObject::~GameObject()
{
	printf("GameObject: %d, destructor\n", _id);
}
