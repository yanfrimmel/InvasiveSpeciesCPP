#pragma once

#include "Vector2d.h" 

struct Memory {
	enum MemoryType { food, water, enemy, mate, stone, stick };
	Vector2d<float> position;
	MemoryType type;
};
