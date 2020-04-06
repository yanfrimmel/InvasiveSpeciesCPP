#ifndef COMMON_H /* Include guard */
#define COMMON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
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
  STONES = 2,
  HUMAN_MALE = 3,
  HUMAN_FEMALE = 4
};

static const TileType tileTypeVector[] = {SOIL, GRASS, STONES, HUMAN_MALE,
                                          HUMAN_FEMALE};

#define FONT_PATH ("assets/fonts/ObliviousFont.ttf")
#define SOIL_IMAGE_PATH ("assets/images/soil.png")
#define GRASS_IMAGE_PATH ("assets/images/grass.png")
#define STONES_IMAGE_PATH ("assets/images/stones.png")
#define HUMAN_MALE_IMAGE_PATH ("assets/images/human_male.png")
#define HUMAN_FEMALE_IMAGE_PATH ("assets/images/human_female.png")

#endif
