#include "Plant.h"

Plant::Plant(Uint32 size, Vector2d<float> position, TileType tileType)
	: GameObject(size, 0, position, tileType)
{
}

void Plant::act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
	if (isDead()) {
		die(gameObjects);
		return;
	}

	consumeTime(fps);

	if (tryToReproduce()) {
		reprodue(gameObjects);
	}
}

auto Plant::consumeTime(float fps) -> void
{
	_hp += 1 / (fps * _grothRate);
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
	gameObjects.emplace_back(createNewPlant(getPosition() + Vector2d<float>(positionChanceX, positionChanceY)));
	_hp -= 1;
	std::cout << "objectList size: " << gameObjects.size() << std::endl;
	std::cout << "new plant: " << _species << std::endl;
}

auto Plant::die(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	std::cout << "death plant: " << this->getId() << std::endl;
	auto end = std::remove_if(gameObjects.begin(), gameObjects.end(),
		[this](std::unique_ptr<GameObject> & o) {
		return this->getId() == o->getId();
	});
	gameObjects.erase(end, gameObjects.end());
}

auto Plant::isDead() -> bool
{
	return _hp <= 0;
}

Plant::~Plant()
{
}
