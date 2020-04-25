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

auto Animal::getSpecies() -> Species
{
	return _species;
}

auto Animal::getMaxMultipleBirth() -> int
{
	return _MAX_MULTIPLE_BIRTH;
}

auto Animal::isDead() -> bool
{
	return _hp <= 0;
}

auto Animal::die(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	std::cout << "death: " << this->getId() << std::endl;
	auto end = std::remove_if(gameObjects.begin(), gameObjects.end(),
		[this](std::unique_ptr<GameObject> & o) {
		return this->getId() == o->getId();
	});
	gameObjects.erase(end, gameObjects.end());
}

auto Animal::consumeTime(float fps) -> void
{
	auto timePassed = 1 / fps;
	_age += timePassed;
	if(_hydration > 0) _hydration -= timePassed;
	else _hp -= timePassed;
	if (_nutrition > 0) _nutrition -= timePassed;
	else _hp -= timePassed;

}

void Animal::act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
	if (isDead()) {
		die(gameObjects);
		return;
	}

	consumeTime(fps);

	if (_gender == female && _numberOfFetuses > 0) {
		tryGiveLabor(gameObjects);
	}

	if (_isPlayer) return;

	for (auto& obj : gameObjects) {
		if (this != obj.get() && isInSight(*obj.get()) && ((Animal*)obj.get())->getSpecies() == _species) {
			auto mate = ((Animal*)obj.get());
			if (tryToMate(*mate)) {
				onDestinationSelected(mate->getPosition(), fps);
				if (isReachedDestination(mate->getPosition())) {
					mateWith(*mate);
				}
				resetTargetPosition();
				return;
			}
		}
	}

	if (!hasTargetPostion()) {
		_targetPosition = { globalParams::worldWidth * globalRNG::rng(), globalParams::worldHeight * globalRNG::rng() };
		//std::cout << "id: " << _id << ", _targetPosition: " << _targetPosition.x << ", " << _targetPosition.y << std::endl;
	}

	if (isReachedDestination(_targetPosition)) {
		resetTargetPosition();
	}
	onDestinationSelected(_targetPosition, fps);
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
		partner.getGender() == female &&
		partner._numberOfFetuses == 0 &&
		_hydration >= _MAX_HYDRATION / 4 &&
		_nutrition >= _MAX_NUTRITION / 4;
}

void Animal::mateWith(Animal & partner)
{
	this->_hydration -= _MAX_HYDRATION / 4; // TODO: find a better way
	this->_nutrition -= _MAX_NUTRITION / 4; // TODO: find a better way
	partner.setHydration(partner.getHydration() - _MAX_HYDRATION / 4);
	partner.setNutrition(partner.getNutrition() - _MAX_NUTRITION / 4);
	if (partner.getNumberOfFetuses() > 0) return;
	auto chanceOfPregnancy = globalRNG::rng();
	if (chanceOfPregnancy > 0.5) { // TODO: change this
		partner.setTimeOfStartOfPregnancy(partner.getAge());
		auto fetuses = (float)partner.getMaxMultipleBirth() *  globalRNG::rng();
		partner.setNumberOfFetuses((int)fetuses);
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

void Animal::tryGiveLabor(std::vector<std::unique_ptr<GameObject>>& objectList)
{
	if (_PREGNANCY_TIME + _timeOfStartOfPregnancy <= _age) {
		while (_numberOfFetuses > 0) {
			auto chanceOfMale = globalRNG::rng();
			Animal::Gender gender;
			if (chanceOfMale > 0.5) {
				gender = male;
			}
			else {
				gender = female;
			}
			objectList.emplace_back(createNewAnimal(gender,
				getPosition() + Vector2d<int>(_numberOfFetuses, _numberOfFetuses) * _size / 2));
			std::cout << "objectList size: " << objectList.size() << std::endl;
			std::cout << "birth: " << gender << std::endl;
			--_numberOfFetuses;
		}
		_hp -= _MAX_HP / 2;
		_timeOfStartOfPregnancy = 0;
		_numberOfFetuses = 0;
	}
}

//void Animal::think(std::vector<GameObject> objectsInSight, float fps) {
//	std::cout << "shit" << std::endl;
//};

Animal::~Animal()
{
}