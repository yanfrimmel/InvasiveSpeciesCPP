#include "Graphics.h"

Graphics::Graphics(Uint32 windowWidth, Uint32 windowHeight, Uint32 flags)
    : _windowWidth(windowWidth), _windowHeight(windowHeight), _flags(flags) {
  if (initializeSdl()) {
    _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
        createWindow(), SDL_DestroyWindow);
    _renderer =
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>(
            createRenderer(), SDL_DestroyRenderer);
    _textures = std::unique_ptr<
        std::map<TileType, SDL_Texture *>,
        std::function<void(std::map<TileType, SDL_Texture *> *)>>(
        loadAllTextures(), Graphics::destroyAllTextures);
    _baseTile =
        std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>>(
            createBaseRect(), destroyRectAndTexture);
    _globalFont = std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>>(
        createRegularFont(), destroyFont);
    std::cout << "Graphics created\n";
  }
}

auto Graphics::initializeSdl() -> bool {
  // attempt to initialize graphics and timer system
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    std::cout << "error initializing SDL: \n" << SDL_GetError();
    return false;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cout << "could not initialize sdl2_image: \n" << IMG_GetError();
    return false;
  }
  if (TTF_Init() == -1) {
    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: \n"
              << TTF_GetError();
    return false;
  }
  return true;
}

auto Graphics::createWindow() -> SDL_Window * {
  SDL_Window *window = SDL_CreateWindow(
      "InvasiveSpecies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      _windowWidth, _windowHeight, _flags);
  if (!window) {
    std::cout << "error creating window: \n" << SDL_GetError();
    SDL_Quit();
    return nullptr;
  }
  return window;
}

auto Graphics::createRenderer() -> SDL_Renderer * {
  // create a renderer, which sets up the graphics hardware
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;

  SDL_Renderer *renderer = SDL_CreateRenderer(_window.get(), -1, render_flags);
  if (!renderer) {
    std::cout << "error creating renderer: \n" << SDL_GetError();
    quitSdl();
    return nullptr;
  }

  return renderer;
}

auto Graphics::loadTexture(const char *imagePath) -> SDL_Texture * {
  SDL_Texture *texture = IMG_LoadTexture(_renderer.get(), imagePath);
  if (!texture) {
    std::cout << "error creating texture\n";
    quitSdl();
    return nullptr;
  }
  return texture;
}

auto Graphics::createRectFromTexture(SDL_Texture *texture) -> RectAndTexture * {
  auto *dest = new SDL_Rect();
  SDL_QueryTexture(texture, nullptr, nullptr, &dest->w, &dest->h);
  auto *rectAndTexture = new RectAndTexture{dest, texture};
  return rectAndTexture;
}

auto Graphics::createBaseRect() -> RectAndTexture * {
  RectAndTexture *baseTile = createRectFromTexture((*_textures)[SOIL]);
  return baseTile;
}

auto Graphics::clearRender() -> void { SDL_RenderClear(_renderer.get()); }

auto Graphics::presentRender() -> void { SDL_RenderPresent(_renderer.get()); }

auto Graphics::renderGrid(
    const std::vector<std::pair<TileType, SDL_Point>> &gameObjectsPositionsMap)
    -> void {
  renderGridBackground();
  renderGameObjects(gameObjectsPositionsMap);
}

auto Graphics::renderGameObjects(
    const std::vector<std::pair<TileType, SDL_Point>> &gameObjectsPositionsMap)
    -> void {
  for (const auto &current : gameObjectsPositionsMap) {
    _baseTile->texture = (*_textures)[current.first];
    _baseTile->rect->x = current.second.x;
    _baseTile->rect->y = current.second.y;
    renderTexture(_baseTile.get());
  }
}

auto Graphics::renderGridBackground() -> void {
  // printf("renderGridBackground\n");
  int tileWidth = _baseTile->rect->w;
  int tileHeight = _baseTile->rect->h;
  _baseTile->texture = (*_textures)[SOIL];
  for (int i = 0; i < _windowWidth; i += tileWidth) {
    for (int j = 0; j < _windowHeight; j += tileHeight) {
      _baseTile->rect->x = i;
      _baseTile->rect->y = j;
      renderTexture(_baseTile.get());
    }
  }
}

auto Graphics::renderTexture(RectAndTexture *rectAndTexture) -> void {
  SDL_RenderCopy(_renderer.get(), rectAndTexture->texture, nullptr,
                 rectAndTexture->rect);
}

auto Graphics::getImagePathStringByTileType(TileType tileType) -> const char * {
  switch (tileType) {
  case TileType::SOIL:
    return SOIL_IMAGE_PATH;
  case TileType::GRASS:
    return GRASS_IMAGE_PATH;
  case TileType::STONES:
    return STONES_IMAGE_PATH;
  case TileType::HUMAN_MALE:
    return HUMAN_MALE_IMAGE_PATH;
  case TileType::HUMAN_FEMALE:
    return HUMAN_FEMALE_IMAGE_PATH;
  default:
    break;
  }
  return nullptr;
}

auto Graphics::loadAllTextures() -> std::map<TileType, SDL_Texture *> * {
  auto texturesMap = new std::map<TileType, SDL_Texture *>();
  for (auto currentTileType : tileTypeVector) {
    (*texturesMap)[currentTileType] =
        loadTexture(getImagePathStringByTileType(currentTileType));
  }
  return texturesMap;
}

auto Graphics::destroyAllTextures(
    std::map<TileType, SDL_Texture *> *texturesMap) -> void {
  for (auto const &p : *texturesMap) {
    SDL_DestroyTexture(p.second);
  }

  texturesMap->clear();
  delete texturesMap;
  std::cout << "destroyAllTextures done\n";
}

auto Graphics::destroyFont(TTF_Font *font) -> void {
  TTF_CloseFont(font);
  std::cout << "destroyFont done\n";
}

auto Graphics::destroyRectAndTexture(RectAndTexture *rectAndTexture) -> void {
  delete rectAndTexture->rect;
  //    SDL_DestroyTexture(rectAndTexture->texture); //already freed at
  //    destroyAllTextures()
  delete rectAndTexture;
}

auto Graphics::renderText(const std::string &textureText, SDL_Color textColor,
                          int x, int y) -> void {
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(_globalFont.get(), textureText.c_str(), textColor);
  SDL_Texture *textTexture = nullptr;
  if (textSurface == nullptr) {
    std::cout << "Unable to render text surface! SDL_ttf Error: \n",
        TTF_GetError();
  } else {
    // Create texture from surface pixels
    textTexture = SDL_CreateTextureFromSurface(_renderer.get(), textSurface);
    if (textTexture == nullptr) {
      std::cout << "Unable to create texture from rendered text! SDL Error: \n"
                << SDL_GetError();
    } else {
      std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>>
          baseTile = std::unique_ptr<RectAndTexture,
                                     std::function<void(RectAndTexture *)>>(
              createRectFromTexture(textTexture), destroyRectAndTexture);
      baseTile->rect->x = x;
      baseTile->rect->y = y;
      renderTexture(baseTile.get());
      baseTile.reset();
      SDL_DestroyTexture(textTexture);
    }

    // Get rid of old surface
    SDL_FreeSurface(textSurface);
  }
}

auto Graphics::getFontFromFile(const char *file, int ptsize) -> TTF_Font * {
  TTF_Font *gFont = TTF_OpenFont(file, ptsize);

  if (gFont == nullptr) {
    std::cout << "Failed to load lazy font! SDL_ttf Error: \n"
              << TTF_GetError();
  }

  return gFont;
}

auto Graphics::createRegularFont() -> TTF_Font * {
  return getFontFromFile(FONT_PATH, FONT_SIZE);
}

auto Graphics::quitSdl() -> void {
  // these must be here or else they will get called after SDL_Quit()
  _globalFont.reset();
  _textures.reset();
  _baseTile.reset();
  _renderer.reset();
  _window.reset();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

Graphics::~Graphics() {
  std::cout << "Graphics destructor\n";
  quitSdl();
}
