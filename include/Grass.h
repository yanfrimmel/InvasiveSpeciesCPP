#pragma once

#include "Plant.h"

class Grass : public Plant {

public:
	Grass(Vector2d<float> position);
	std::unique_ptr<Plant> createNewPlant(Vector2d<float> position);
};