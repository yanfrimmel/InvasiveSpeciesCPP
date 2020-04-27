#pragma once

#include "GameObject.h"

class Plant : public GameObject {

public:
	enum Species { grass, cherry };
	Plant(Uint32 size, Vector2d<float> position, TileType tileType);
	virtual void act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps);
	virtual std::unique_ptr<Plant> createNewPlant(Vector2d<float> position) = 0;
	Type getType();
	auto beEaten(float nutrition) -> float; // return the number of successfully consumed plant
	virtual ~Plant();

protected:
	float _grothSparsityIndex = 4;
	float _growthRate = 1; //seconds hp per second recovery
	Species _species;
	float _MAX_HP_BEFORE_REPRODUCTION = 10; 
	float _hp = 1; // also the amount of nutrition provided once eaten
	auto consumeTime(float fps) -> void;
	auto tryToReproduce() -> bool;
	auto reprodue(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void;
	auto removeObject(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void;
	auto isDead() -> bool;
};