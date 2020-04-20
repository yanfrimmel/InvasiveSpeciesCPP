#include "Animal.h"

auto Animal::resetTargetPosition() -> void
{
	_targetPosition.x = -1;
}

auto Animal::hasTargetPostion() -> bool
{
	return _targetPosition.x >= 0;
}

Animal::Animal(Uint32 size, Uint32 speed, Vector2d<float> position, TileType tileType)
	: GameObject(size, speed, position, tileType)
{
	resetTargetPosition();
}

auto Animal::getMaxMultipleBirth() -> int
{
	return _MAX_MULTIPLE_BIRTH;
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
auto Animal::setNumberOfFetuses(int fetuses) -> void
{
	_numberOfFetuses = fetuses;
}

auto Animal::setTimeOfStartOfPregnancy(float timeOfStartOfPregnancy) -> void
{
	_timeOfStartOfPregnancy = timeOfStartOfPregnancy;
}

auto Animal::setHydration(float hydration) -> void
{
	_hydration = hydration;
}

auto Animal::setNutrition(float nutrition) -> void
{
	_nutrition = nutrition;
}

auto Animal::isInSight(GameObject& object) -> bool
{
	return Vector2d<float>::distance(getPosition(), object.getPosition()) <= _sight;
}

auto Animal::tryToMate(Animal & partner) -> bool
{
	return typeid(*this) == typeid(partner) &&
		_gender == male &&
		_hp == _MAX_HP &&
		_hydration >= _MAX_HYDRATION / 4 &&
		_nutrition >= _MAX_NUTRITION / 4 &&
		partner.getGender() == female && 
		partner._numberOfFetuses == 0;
}

void Animal::mateWith(Animal & partner)
{
	this->_hydration /= 2; // TODO: find a better way
	this->_nutrition /= 2; // TODO: find a better way
	partner.setHydration(partner.getHydration() / 2);
	partner.setNutrition(partner.getNutrition() / 2);
	if (partner.getNumberOfFetuses() > 0) return;
	auto chanceOfPregnancy = globalRNG::rng();
	if (chanceOfPregnancy > 0.5) {
		partner.setTimeOfStartOfPregnancy(partner.getAge());
		auto fetuses = (float)partner.getMaxMultipleBirth() *  globalRNG::rng();
		partner.setNumberOfFetuses((int)fetuses);
		std::cout << "fetuses: " << fetuses << std::endl;
	}
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

auto Animal::getNumberOfFetuses() -> int
{
	return _numberOfFetuses;
}

//void Animal::think(std::vector<GameObject> objectsInSight, float fps) {
//	std::cout << "shit" << std::endl;
//};

Animal::~Animal()
{
}