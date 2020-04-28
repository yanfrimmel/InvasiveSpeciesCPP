#include "GameState.h"

GameState::GameState(unsigned short int windowWidth, unsigned short int windowHeight)
{
	//TODO: init positions from a map file
	_gameObjects.emplace_back(new Grass({ 100 , 150 }));
	_gameObjects.emplace_back(new Grass({ 1732 , 350 }));
	_gameObjects.emplace_back(new Grass({ 550 , 1700 }));
	_gameObjects.emplace_back(new Grass({ 660 , 590 }));
	_gameObjects.emplace_back(new Grass({ 670 , 1520 }));
	_gameObjects.emplace_back(new Grass({ 770 , 1520 }));
	_gameObjects.emplace_back(new Grass({ 580 , 510 }));
	_gameObjects.emplace_back(new Grass({ 580 , 620 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 220 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 520 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 620 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 720 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 820 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 920 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 1120 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 1180 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 1320 }));
	_gameObjects.emplace_back(new Grass({ 400 , 1420 }));
	_gameObjects.emplace_back(new Grass({ 400 , 1720 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 1820 }));
	_gameObjects.emplace_back(new Grass({ 570 , 650 }));
	_gameObjects.emplace_back(new Grass({ 1600 , 1650 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 100 }));
	_gameObjects.emplace_back(new Grass({ 1600 , 200 }));
	_gameObjects.emplace_back(new Grass({ 1600 , 1700 }));
	_gameObjects.emplace_back(new Grass({ 100 , 1700 }));
	_gameObjects.emplace_back(new Grass({ 1200 , 1200 }));
	_gameObjects.emplace_back(new Water(32, { 100 , 100 }));
	_gameObjects.emplace_back(new Water(32, { 1000 , 1016 }));
	_gameObjects.emplace_back(new Water(32, { 1016 , 1000 }));
	_gameObjects.emplace_back(new Grass({ 1200 , 1220 }));
	_gameObjects.emplace_back(new Grass({ 1200 , 1260 }));
	_gameObjects.emplace_back(new Grass({ 1220 , 1280 }));
	_gameObjects.emplace_back(new Grass({ 1280 , 1280 }));
	_gameObjects.emplace_back(new Grass({ 1280 , 1310 }));
	_gameObjects.emplace_back(new Water(32, { 1930 , 40 }));
	_gameObjects.emplace_back(new Water(32, { 50 , 1900 }));
	_gameObjects.emplace_back(new Water(32, { 1900 , 1900 }));
	_gameObjects.emplace_back(new Grass({ 1060 , 1030 }));
	_gameObjects.emplace_back(new Grass({ 1040 , 1032 }));
	_gameObjects.emplace_back(new Grass({ 1000 , 1050 }));
	_gameObjects.emplace_back(new Human(Animal::female, { 900, 600 }));
	_gameObjects.emplace_back(new Human(Animal::female, { 1000, 700 }));
	_gameObjects.emplace_back(new Human(Animal::male, { 900, 700 }));
	_player = _gameObjects.back().get();
	_player->setAsPlayer();

	initCameraPosition(windowWidth, windowHeight);
}

auto GameState::initCameraPosition(unsigned short int windowWidth, unsigned short int windowHeight) -> void {
	_camera = { (_player->getPosition().x - windowWidth / 2), (_player->getPosition().y - windowHeight / 2) };
}

auto GameState::getCamera() -> Vector2d<float> { return _camera; }

auto GameState::setCamera(Vector2d<float> camera) -> void { _camera = camera; }

auto GameState::getPlayer() -> GameObject& { return *_player; }

auto GameState::getGameObjects() ->std::vector<std::unique_ptr<GameObject>>& {
	return _gameObjects;
}

auto GameState::updateGameObjects(float fps) -> void
{
	if (fps <= 0) return;
	for (unsigned int i = 0; i < _gameObjects.size(); i++) {
		auto & gameObjecet = _gameObjects[i];
		if ((gameObjecet.get())) {
			gameObjecet.get()->act(_gameObjects, fps);
		}
	}
}

GameState::~GameState() {
	std::cout << "GameState destructor\n";
	_gameObjects.clear();
	_gameObjects.shrink_to_fit();
}
