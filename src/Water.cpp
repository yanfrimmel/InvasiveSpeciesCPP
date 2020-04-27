#include "Water.h"

Water::Water(Uint32 size, Vector2d<float> position) : GameObject(size, 0, position, WATER)
{
}

float Water::drink(float hydration, std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
	if (_mass > hydration) {
		_mass -= hydration;
		return hydration;
	}
	else
	{
		removeObject(gameObjects);
		return _mass;
	}
}

void Water::act(std::vector<std::unique_ptr<GameObject>>& gameObjects, float fps)
{
}

GameObject::Type Water::getType()
{
	return water;
}

auto Water::removeObject(std::vector<std::unique_ptr<GameObject>>& gameObjects) -> void
{
	std::cout << "out of water: " << this->getId() << std::endl;
	GameObject::removeObject(gameObjects);
}
