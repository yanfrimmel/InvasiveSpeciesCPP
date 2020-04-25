#pragma once

#include "Animal.h"


class Human :
	public Animal
{
public:
	Human(Gender gender, Vector2d<float> position);
	auto throwObject(GameObject& object, Vector2d<float> target)->void;
	void act(std::vector<std::unique_ptr<GameObject>>& objectsInSight, float fps);
	auto createNewAnimal(Gender gender, Vector2d<float> position)->std::unique_ptr<Animal>;
	bool tryToEat(GameObject& food);
};

