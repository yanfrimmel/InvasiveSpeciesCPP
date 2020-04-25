#include "Grass.h"

Grass::Grass(Vector2d<float> position) : Plant(32, position, GRASS)
{
	_hp = 1;
	_species = grass;
	_MAX_HP_BEFORE_REPRODUCTION = 10;
	_grothSparsityIndex = 4;
	_grothRate = 10;
}

auto Grass::createNewPlant(Vector2d<float> position) -> std::unique_ptr<Plant>
{
	return std::make_unique<Grass>(position);
}
