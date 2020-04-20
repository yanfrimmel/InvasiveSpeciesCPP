#include "Human.h"
#include "Common.h"
Human::Human(Gender gender, Vector2d<float> position) :
	Animal(32, gender == male ? 100 : 95, position, gender == male ? HUMAN_MALE : HUMAN_FEMALE)
{
	_MAX_HP = 100;
	_MAX_HYDRATION = 100;
	_MAX_NUTRITION = 100;
	_PREGNANCY_TIME = 9;
	_gender = gender;
	_hp = _MAX_HP;
	_hydration = _MAX_HYDRATION;
	_nutrition = _MAX_NUTRITION;
	_sight = 300;
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

void Human::think(std::vector<std::unique_ptr<GameObject>>& objectsInSight, float fps)
{
	_age += 1 / (fps); //TODO * 60

	if (_gender == female && _timeOfStartOfPregnancy > 0) {
		tryGiveLabor(objectsInSight);
	}

	if (_isPlayer) return;

	for (auto& obj : objectsInSight) {
		if (this != obj.get() && isInSight(*obj.get()) && dynamic_cast<Human*> (obj.get())) {
			auto mate = ((Human*)obj.get());
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
		std::cout << "id: " << _id << ", _targetPosition: " << _targetPosition.x <<", " << _targetPosition.y << std::endl;
	}

	if (isReachedDestination(_targetPosition)) {
		resetTargetPosition();
	}
	onDestinationSelected(_targetPosition, fps);
	
}

void Human::tryGiveLabor(std::vector<std::unique_ptr<GameObject>>& objectList)
{
	if (_PREGNANCY_TIME + _timeOfStartOfPregnancy <= _age ) {
		while (_numberOfFetuses > 0) {
			auto chanceOfMale = globalRNG::rng();
			Animal::Gender gender;
			if (chanceOfMale > 0.5) {
				gender = male;
			}
			else {
				gender = female;
			}
			objectList.emplace_back(new Human(gender,
				getPosition() +  Vector2d<float>((float)_numberOfFetuses , (float)_numberOfFetuses) * _size/2 ) );
			std::cout << "birth: " << _gender << std::endl;
			--_numberOfFetuses;
		}
		_timeOfStartOfPregnancy = 0;
		_numberOfFetuses = 0;
	}
}
