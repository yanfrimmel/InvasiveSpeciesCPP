#include "Plant.h"

Plant::Plant(Uint32 size, Vector2d<float> position, TileType tileType)
	: GameObject(size, 0, position, tileType)
{
}

void Plant::act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
	if (isDead()) {
		removeObject(gameObjects);
		return;
	}

	consumeTime(fps);

	if (gameObjects.size() <= 1000 && tryToReproduce()) { //TODO: find a better way to fix bad performance
		reprodue(gameObjects);
	}
}

auto Plant::consumeTime(float fps) -> void
{
	_hp += _growthRate * 1 / fps;
}

auto Plant::tryToReproduce() -> bool
{
	return _hp > _MAX_HP_BEFORE_REPRODUCTION;
}

auto Plant::reprodue(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	auto xChance = globalRNG::rng();
	auto yChance = globalRNG::rng();
	auto positionChanceX = xChance * (xChance > 0.5 ? _grothSparsityIndex : -_grothSparsityIndex) * _size;
	auto positionChanceY = yChance * (yChance > 0.5 ? _grothSparsityIndex : -_grothSparsityIndex) * _size;
	gameObjects.emplace(gameObjects.begin(), createNewPlant(getPosition() + Vector2d<float>(positionChanceX, positionChanceY)));
	_hp -= 1;
	std::cout << "objectList size: " << gameObjects.size() << std::endl;
	std::cout << "new plant: " << _species << std::endl;
}

auto Plant::removeObject(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	std::cout << "death plant: " << this->getId() << std::endl;
	GameObject::removeObject(gameObjects);
}

auto Plant::isDead() -> bool
{
	return _hp <= 0;
}

GameObject::Type Plant::getType()
{
	return plant;
}

auto Plant::beEaten(float nutrition) -> float
{
	if (_hp > nutrition) {
		_hp -= nutrition;
		return nutrition;
	}
	else
	{
		auto temp = _hp;
		_hp = 0;
		return temp;
	}
}

Plant::~Plant()
{
}
