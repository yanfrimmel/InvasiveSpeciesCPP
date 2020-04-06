#include "GameState.h"

GameState::GameState(unsigned short int windowWidth,
                     unsigned short int windowHeight) {
  _camera = {0, 0};
  //    _gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200
  //    ,{(float)windowWidth/2 - 100, (float)windowHeight/2}, HUMAN_FEMALE));
  //    _gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200
  //    ,{(float)windowWidth/2 - 50, (float)windowHeight/2 -50}, HUMAN_FEMALE));
  //    _gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200
  //    ,{(float)windowWidth/2 - 20, (float)windowHeight/2}, HUMAN_FEMALE));
  //    _gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE, 200
  //    ,{(float)windowWidth/2 - 100, (float)windowHeight/2 +200},
  //    HUMAN_FEMALE)); _gameObjects.push_back(GameObject(DEFAULT_OBJECT_SIZE,
  //    200 ,{(float)windowWidth/2 -400, (float)windowHeight/2 + 100},
  //    HUMAN_MALE));
  _gameObjects.push_back(GameObject(
      DEFAULT_OBJECT_SIZE, 200,
      {(float)windowWidth / 2, (float)windowHeight / 2}, HUMAN_MALE));
  _player = &_gameObjects.at(_gameObjects.size() - 1);
}

auto GameState::getCamera() -> Vector2d<float> { return _camera; }

auto GameState::setCamera(Vector2d<float> camera) -> void { _camera = camera; }

auto GameState::getPlayer() -> GameObject * { return _player; }

auto GameState::getGameObjects() -> std::vector<GameObject> {
  return _gameObjects;
}

GameState::~GameState() {
  std::cout << "GameState destructor\n";
  _gameObjects.clear();
  _gameObjects.shrink_to_fit();
}
