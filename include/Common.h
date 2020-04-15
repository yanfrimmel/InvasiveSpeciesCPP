#pragma once

#ifdef __unix__         
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#elif defined(_WIN32) || defined(WIN32) 
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#endif

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <queue>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <typeinfo>

template <typename F>
auto compose(F&& f)
{
	return[a = std::move(f)](auto&&... args){
		return a(std::move(args)...);
	};
}

struct Configurations {
	Uint32 windowWidth;
	Uint32 windowHeight;
	Uint32 flags;
	Uint32 fpsCap;
	Uint32 worldWidth;
	Uint32 worldHeight;
};

struct RectAndTexture {
	SDL_Rect *rect;
	SDL_Texture *texture;
};

struct MouseInput {
	int mouseX;
	int mouseY;
	Uint32 mouseState;
};

enum TileType {
	SOIL = 0,
	GRASS = 1,
	STONE = 2,
	HUMAN_MALE = 3,
	HUMAN_FEMALE = 4,
	CHICKEN_MALE = 5,
	CHICKEN_FEMALE = 6,
	WATER = 7
};

static const TileType tileTypeVector[] = { SOIL, GRASS, STONE, HUMAN_MALE,
										  HUMAN_FEMALE, CHICKEN_MALE, CHICKEN_FEMALE, WATER };

#define FONT_PATH ("assets/fonts/ObliviousFont.ttf")
#define SOIL_IMAGE_PATH ("assets/images/soil.png")
#define GRASS_IMAGE_PATH ("assets/images/grass.png")
#define STONE_IMAGE_PATH ("assets/images/stone.png")
#define HUMAN_MALE_IMAGE_PATH ("assets/images/human_male.png")
#define HUMAN_FEMALE_IMAGE_PATH ("assets/images/human_female.png")
#define CHICKEN_MALE_IMAGE_PATH ("assets/images/chicken_male.png")
#define CHICKEN_FEMALE_IMAGE_PATH ("assets/images/chicken_female.png")
#define WATER_IMAGE_PATH ("assets/images/water.png")
