#pragma once

#include "GameObject.h"

class Water : public GameObject {

public:
	Water(Uint32 size, Vector2d<float> position);
	auto drink(float hydration, std::vector<std::unique_ptr<GameObject>>& gameObjects) -> float; // return the number of successfully consumed water
	void act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps);
	GameObject::Type getType();

protected:
	float _mass = 10000; // equal to the value of hydration once drunk
	auto removeObject(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void;
};
