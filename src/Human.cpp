#include "Human.h"
#include "Common.h"

Human::Human(Gender gender, Vector2d<float> position) :
	Animal(32, gender == male ? 400 : 395, position, gender == male ? HUMAN_MALE : HUMAN_FEMALE)
{
	_species = human;
	_MAX_HP = 100;
	_MAX_HYDRATION = 100;
	_MAX_NUTRITION = 100;
	_PREGNANCY_TIME = 20; //seconds 
	_gender = gender;
	_hp = _MAX_HP;
	_hydration = _MAX_HYDRATION;
	_nutrition = _MAX_NUTRITION;
	_sight = 300;
	_diet = omnivore;
	if (_gender == male) {
		_MAX_MULTIPLE_BIRTH = 0;
		_strength = 10.0F;
		_agility = 0.7F;
	}
	else {
		_MAX_MULTIPLE_BIRTH = 4;
		_strength = 8.0F;
		_agility = 0.6F;
	}
}

void Human::act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
	Animal::act(gameObjects, fps);
}

auto Human::createNewAnimal(Gender gender, Vector2d<float> position) -> std::unique_ptr<Animal>
{
	return std::make_unique<Human>(gender, position);
}

bool Human::tryToEat(GameObject & food)
{
	return _nutrition < _MAX_NUTRITION/2 &&
		(food.getType() == plant || 
		(food.getType() == animal && ((Animal*)&food)->getSpecies() != _species));
}
