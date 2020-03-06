#ifndef COMMON_H /* Include guard */
#define COMMON_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_error.h>
#include <memory>
#include <functional>
#include <list>

struct Configurations
{
	unsigned short int windowWidth;
	unsigned short int windowHeight;
	Uint32 flags;
	Uint32 fpsCap;
};

struct RectAndTexture
{
	SDL_Rect *rect;
	SDL_Texture *texture;
};

struct MouseInput
{
	int mouseX;
	int mouseY;
	Uint32 mouseState;
};

struct GameObject
{
	Uint32 id;
	Uint32 speed;
	SDL_Point position;
	SDL_Texture *texture;

};

struct GameState
{
	SDL_Point camera;
	GameObject player;
	std::list<GameObject> gameObjects;
};

#endif
