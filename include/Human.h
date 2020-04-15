#pragma once

#include "Animal.h"


class Human :
	public Animal
{
public:
	Human(Gender gender, Vector2d<float> position);
	auto throwObject(GameObject object, Vector2d<float> target)->void;
	void think(std::vector<std::unique_ptr<GameObject>>& objectsInSight, float fps);
	void mateWith(Animal& partner);
};

