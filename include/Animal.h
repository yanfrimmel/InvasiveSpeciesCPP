#pragma once

#include "GameObject.h"
#include "Memory.h"

class Animal : public GameObject {

public:
	enum Gender { male, female };
	enum Diet { herbivore, omnivore, carnivore };
	enum Behavior { lonesome, social, humanoid };

protected:
	float _MAX_HP = 100;
	float _MAX_HYDRATION = 100;
	float _MAX_NUTRITION = 100;
	int _MAX_MULTIPLE_BIRTH = 10;
	float _PREGNANCY_TIME = 10; // 1 = minute
	Vector2d<float> _targetPosition;
	Gender _gender;
	Diet _diet;
	Behavior _behavior;
	float _hp; // 0 is dead, up to species limit
	float _hydration; // up to species limit, on 0 hp starts to decrease
	float _nutrition; // up to species limit, on 0 hp starts to decrease
	float _age = 0; // used for timing of actions - in minutes
	float _strength; //the damage per second that can inflict up to species limit
	float _agility; //the change to inflict damage or to dodge, up to species limit (between 0 to 1)
	float _sight; // the radius in pixels that the animal can "see" other game objects
	float _mass; //the amount of meat provided once dead
	int _memorySize; // maximum memory size, up to species limit
	bool _sleeping;
	int _numberOfFetuses = 0;
	float _timeOfStartOfPregnancy = 0;
	std::vector<Memory> _memory; // objects that the animal "remembers" as they were when he/she last saw them
	auto resetTargetPosition() -> void;
	auto hasTargetPostion() -> bool;
//protected:
//	auto setGender(Gender)->void;
//	auto setDiet(Diet)->void;
//	auto setBehavior(Behavior)->void;
//	auto setSleeping(bool)->void;
//	auto setHp(float)->void;
//	auto setStrength(float)->void;
//	auto setAgility(float)->void;
//	auto setSight(float)->void;
//	auto setMass(float)->void;
//	auto setMemorySize(int)->void;

public:
	Animal(Uint32 size, Uint32 speed, Vector2d<float> position, TileType tileType);
	auto isDead() -> bool;
	auto getGender()->Gender;
	auto getDiet()->Diet;
	auto getBehavior()->Behavior;
	auto isSleeping()->bool;
	auto getHp()-> float;
	auto getStrength()->float;
	auto getAgility()->float;
	auto getSight()->float;
	auto getMass()->float;
	auto getMemoerySize()->int;
	auto getHydration()->float;
	auto getNutrition()->float;
	auto getAge()->float;
	auto getMemory()->std::vector<Memory>&;
	auto attack(Animal& victim)->void;
	auto eat(GameObject& food)->void;
	auto goToSleep()->void; // this will recover hp
	auto awake()->void;
	auto mateWith(Animal& partner) -> void;
	virtual void think(std::vector<std::unique_ptr<GameObject>>& objectsInSight, float fps) = 0;
	virtual void tryGiveLabor(std::vector<std::unique_ptr<GameObject>>& gameObjects) = 0;
	auto tryToRemember(GameObject objectToRemeber)->void; // if reached max memory size forget the oldest memory
	auto isInSight(GameObject& object) -> bool;
	auto tryToMate(Animal& partner) -> bool;
	auto setHydration(float)->void;
	auto setNutrition(float)->void;
	auto setTimeOfStartOfPregnancy(float) -> void;
	auto setNumberOfFetuses(int) -> void;
	auto getNumberOfFetuses() -> int;
	auto getMaxMultipleBirth() -> int;
	
	virtual ~Animal();
};

