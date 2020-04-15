#include "Human.h"

Human::Human(Gender gender, Vector2d<float> position) : 
	Animal(32, gender == male ? 100 : 95, position, gender == male ? HUMAN_MALE : HUMAN_FEMALE)
{
	_MAX_HP = 100;
	_MAX_HYDRATION = 100;
	_MAX_NUTRITION = 100;
	_gender = gender;
	_hp = _MAX_HP;
	_hydration = _MAX_HYDRATION;
	_nutrition = _MAX_NUTRITION;
	_sight = 200;
	if (_gender == male) {
		_strength = 10;
		_agility = 0.7;
	}
	else {
		_strength = 8;
		_agility = 0.6;
	}
}

void Human::think(std::vector<std::unique_ptr<GameObject>>& objectsInSight, float fps)
{
	for (auto& obj : objectsInSight) {
		if (this != obj.get() && isInSight(*obj.get()) && dynamic_cast<Human*> (obj.get())) {
			tryToMate(*((Human*)obj.get()), fps);
		}
	}
}

void Human::mateWith(Animal & partner)
{
}
