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

auto Animal::removeObject(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	std::cout << "death: " << this->getId() << std::endl;
	GameObject::removeObject(gameObjects);
}

auto Animal::consumeTime(float fps) -> void
{
	auto timePassed = 1 / fps;
	_age += timePassed;
	auto metabolism = timePassed / 10;
	if(_hydration > 0) _hydration -= metabolism;
	else {
		_hp -= metabolism;
	}
	if (_nutrition > 0) _nutrition -= metabolism;
	else {
		_hp -= metabolism;
	}
	if (_hydration > 0 && _nutrition > 0 && _hp <= _MAX_HP - timePassed) _hp += metabolism;
}

void Animal::act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
	if (isDead()) {
		removeObject(gameObjects);
		return;
	}

	consumeTime(fps);

	if (_gender == female && _numberOfFetuses > 0) {
		tryGiveLabor(gameObjects);
	}

	if (_isPlayer) {
		playerAct(gameObjects);
	}

	else {
		aiAct(gameObjects, fps);
	}
}

void Animal::playerAct(std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
	for (auto& obj : gameObjects) {
		if (isReachedDestination(obj->getPosition())) {
			if (tryToMate(*obj.get())) {
				if (isReachedDestination(obj.get()->getPosition())) {
					auto mate = (Animal*)obj.get();
					mateWith(*mate);
				}
				return;
			}
			if (obj.get()->getType() == water) {
				auto water = (Water*)obj.get();
				drink(*water, gameObjects);
				return;
			}
			if (obj.get()->getType() == plant) { //TODO: implement for animal
				auto food = (Plant*)obj.get();
				eatPlant(*food);
				return;
			}
		}
	}
}

void Animal::aiAct(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
	for (auto& obj : gameObjects) {
		if (this != obj.get() && isInSight(*obj.get())) {
			if (tryToMate(*obj.get())) {
				onDestinationSelected(obj->getPosition(), fps);
				if (isReachedDestination(obj.get()->getPosition())) {
					auto mate = (Animal*)obj.get();
					mateWith(*mate);
				}
				resetTargetPosition();
				return;
			}

			if (tryToDrink(*obj.get())) {
				onDestinationSelected(obj->getPosition(), fps);
				if (isReachedDestination(obj->getPosition())) {
					auto water = (Water*)obj.get();
					drink(*water, gameObjects);
				}
				resetTargetPosition();
				return;
			}

			if (tryToEat(*obj.get())) {
				onDestinationSelected(obj->getPosition(), fps);
				if (isReachedDestination(obj->getPosition())) {
					if (obj.get()->getType() == plant) { //TODO: implement for animal
						auto food = (Plant*)obj.get();
						eatPlant(*food);
					}
				}
				resetTargetPosition();
				return;
			}
		}
	}

	if (!hasTargetPostion()) {
		_targetPosition = { globalParams::worldWidth * globalRNG::rng(), globalParams::worldHeight * globalRNG::rng() };
	}

	if (isReachedDestination(_targetPosition)) {
		resetTargetPosition();
	}
	onDestinationSelected(_targetPosition, fps);
}

auto Animal::drink(Water & water, std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	if (_MAX_HYDRATION - _hydration > 1) {
		std::cout << _id << ": hydration: " << _hydration << ", drink: " << water.getId() << std::endl;
		_hydration += water.drink(_MAX_HYDRATION - _hydration, gameObjects);
		std::cout << _id << ": hydration: " << _hydration << ", after" << std::endl;
	}
}

auto Animal::eatPlant(Plant & food) -> void
{
	if (_MAX_NUTRITION - _nutrition > 1) {
		std::cout << _id << ": nutrition: " << _nutrition << ", eats: " << food.getId() << std::endl;
		_nutrition += food.beEaten(_MAX_NUTRITION - _nutrition);
		std::cout << _id << ": nutrition: " << _nutrition << ", after" << std::endl;
	}
}

GameObject::Type Animal::getType()
{
	return animal;
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

auto Animal::tryToMate(GameObject & partner) -> bool
{
	if (partner.getType() == animal) {
		auto mate = (Animal*)&partner;
		return getSpecies() == mate->getSpecies() &&
			_gender == male &&
			_hp == _MAX_HP &&
			mate->getGender() == female &&
			mate->_numberOfFetuses == 0 &&
			_hydration >= _MAX_HYDRATION / 4 &&
			_nutrition >= _MAX_NUTRITION / 4;
	}
	return false;
}

auto Animal::mateWith(Animal & partner) -> void
{
	this->_hydration -= _MAX_HYDRATION / 4; // TODO: find a better way
	this->_nutrition -= _MAX_NUTRITION / 4; // TODO: find a better way
	partner.setHydration(partner.getHydration() - _MAX_HYDRATION / 4);
	partner.setNutrition(partner.getNutrition() - _MAX_NUTRITION / 4);
	if (partner.getNumberOfFetuses() > 0) return;
	auto chanceOfPregnancy = globalRNG::rng();
	if (chanceOfPregnancy > 0.5) {
		partner.setTimeOfStartOfPregnancy(partner.getAge());
		auto fetuses = (float)partner.getMaxMultipleBirth() *  globalRNG::rng();
		std::cout << "successfully pregrancy fetuses: " << fetuses << std::endl;
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

bool Animal::tryToDrink(GameObject & object)
{
	return  object.getType() == water && _hydration < _MAX_HYDRATION / 2;
}

auto Animal::beEaten(float nutrition) -> float
{
	return 0.0F; //TODO: implement

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
			objectList.emplace(objectList.begin(), createNewAnimal(gender,
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

Animal::~Animal()
{
}