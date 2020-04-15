#include "Animal.h"

Animal::Animal(Uint32 size, Uint32 speed, Vector2d<float> position, TileType tileType) 
	: GameObject(size, speed, position, tileType)
{

}

auto Animal::isDead() -> bool
{
	return getHp() <= 0;
}

auto Animal::getGender() -> Gender
{
	return _gender;
}

auto Animal::getDiet() -> Diet
{
	return _diet;
}

auto Animal::getBehavior() -> Behavior
{
	return _behavior;
}

auto Animal::isSleeping() -> bool
{
	return _sleeping;
}

//auto Animal::setGender(Animal::Gender gender) -> void
//{
//	_gender = gender;
//}

//auto Animal::setDiet(Animal::Diet diet) -> void
//{
//	_diet = diet;
//}
//
//auto Animal::setBehavior(Animal::Behavior behavior) -> void
//{
//	_behavior = behavior;
//}

//auto Animal::setSleeping(bool isASleep) -> void
//{
//	_sleeping = isASleep;
//}

//auto Animal::setHp(float hp) -> void
//{
//	_hp = hp;
//}
//
//auto Animal::setStrength(float strength) -> void
//{
//	_strength = strength;
//}
//
//auto Animal::setAgility(float agility) -> void
//{
//	_agility = agility;
//}
//
//auto Animal::setSight(float sight) -> void
//{
//	_sight = sight;
//}
//
//auto Animal::setMass(float mass) -> void
//{
//	_mass = mass;
//}
//
//auto Animal::setMemorySize(int memorySize) -> void
//{
//	_memorySize = memorySize;
//}
//
//auto Animal::setHydration(float hydration) -> void
//{
//	_hydration = hydration;
//}
//
//auto Animal::setNutrition(float nutrition) -> void
//{
//	_nutrition = nutrition;
//}

auto Animal::isInSight(GameObject& object) -> bool
{
	return Vector2d<float>::distance(getPosition(), object.getPosition()) <= _sight;
}

auto Animal::tryToMate(Animal & partner, float fps) -> bool
{
	if (typeid(*this) == typeid(partner) &&
		_gender == male &&
		_hp == _MAX_HP &&
		_hydration >= _MAX_HYDRATION / 4 &&
		_nutrition >= _MAX_NUTRITION / 4 &&
		partner.getGender() == female) {
		onDestinationSelected(partner.getPosition(), fps);
	}
	return false;
}

Animal::~Animal()
{
}

auto Animal::getHp() -> float
{
	return _hp;
}

auto Animal::getStrength() -> float
{
	return _strength;
}

auto Animal::getAgility() -> float
{
	return _agility;
}

auto Animal::getSight() -> float
{
	return _sight;
}

auto Animal::getMass() -> float
{
	return _mass;
}

auto Animal::getMemoerySize() -> int
{
	return _memorySize;
}

auto Animal::getHydration() -> float
{
	return _hydration;
}

auto Animal::getNutrition() -> float
{
	return _nutrition;
}

auto Animal::getAge() -> float
{
	return _age;
}

auto Animal::getMemory() -> std::vector<Memory>&
{
	return _memory;
}

//void Animal::think(std::vector<GameObject> objectsInSight, float fps) {
//	std::cout << "shit" << std::endl;
//};
