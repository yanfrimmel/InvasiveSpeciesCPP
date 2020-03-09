#include "Graphics.h"

Graphics::Graphics(unsigned short int windowWidth, unsigned short int windowHeight, Uint32 flags)
    : _windowWidth{windowWidth}, _windowHeight{windowHeight}, _flags{flags}
{
    if (initializeSdl())
    {
        _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
                      createWindow(),
                      SDL_DestroyWindow
                  );
        _renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>(
                        createRenderer(),
                        SDL_DestroyRenderer
                    );
        _textures = std::unique_ptr<std::map<TileType, SDL_Texture*>,
        std::function<void(std::map<TileType, SDL_Texture*> *)>>(
            loadAllTextures(),
            Graphics::destroyAllTextures
        );
        _baseTile = std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>>(
                        createBaseRect(),
                        destroyRectAndTexture
                    );
        printf("Graphics created\n");
    }
}

bool Graphics::initializeSdl() const
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("could not initialize sdl2_image: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

SDL_Window *Graphics::createWindow()
{
    SDL_Window *window = SDL_CreateWindow("InvasiveSpecies",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          _windowWidth, _windowHeight,
                                          _flags);
    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Log("Could not create a window: %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    return window;
}

SDL_Renderer *Graphics::createRenderer()
{
    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED |
                          SDL_RENDERER_PRESENTVSYNC |
                          SDL_RENDERER_TARGETTEXTURE;

    SDL_Renderer *renderer = SDL_CreateRenderer(_window.get(), -1, render_flags);
    if (!renderer)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_Log("error creating renderer: %s", SDL_GetError());
        quitSdl();
        return NULL;
    }

    return renderer;
}

Uint32 Graphics::calculateFpsAndDelta(Uint32 *startclock, Uint32 *deltaclock) const
{
    Uint32 currentFPS = 0;
    *deltaclock = SDL_GetTicks() - *startclock;
    if (*deltaclock != 0)
    {
        currentFPS = 1000.0f / *deltaclock;
        printf("FPS:%d\n", currentFPS);
    }
    return currentFPS;
}

SDL_Texture *Graphics::loadTexture(const char *imagePath)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer.get(), imagePath);
    if (!texture)
    {
        printf("error creating texture\n");
        SDL_Log("error creating texture: %s", SDL_GetError());
        quitSdl();
        return NULL;
    }
    return texture;
}


RectAndTexture *Graphics::createRectFromTexture(SDL_Texture *texture)
{
    SDL_Rect *dest = new SDL_Rect();
    SDL_QueryTexture(texture, NULL, NULL, &dest->w, &dest->h);
    RectAndTexture *rectAndTexture = new RectAndTexture{dest, texture};
    return rectAndTexture;
}

RectAndTexture *Graphics::createBaseRect()
{
    RectAndTexture *baseTile = createRectFromTexture((*_textures.get())[SOIL]);
    return baseTile;
}

void Graphics::renderTexture(RectAndTexture *rectAndTexture)
{
    SDL_RenderCopy(_renderer.get(), rectAndTexture->texture, NULL, rectAndTexture->rect);
}

void Graphics::renderGrid(std::map<TileType, std::vector<SDL_Rect>> *tilesPositionsMap)
{
    SDL_RenderClear(_renderer.get());
    _baseTile->texture = (*_textures.get())[SOIL];
    // printf("renderGrid\n");
    renderGridBackground(_baseTile.get());
    SDL_RenderPresent(_renderer.get());
}


void Graphics::renderGridBackground(RectAndTexture *baseTile)
{
    // printf("renderGridBackground\n");
    int tileWidth =  baseTile->rect->w;
    int tileHeight = baseTile->rect->h;
    for (int i = 0; i < _windowWidth; i += tileWidth) {
        for (int j = 0; j < _windowHeight; j += tileHeight) {
            renderTexture(baseTile);
            baseTile->rect->x = i;
            baseTile->rect->y = j;
        }
    }
}

const char* Graphics::getImagePathStringByTileType(TileType tileType)
{
    switch (tileType)
    {
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
    }
    return nullptr;
}

std::map<TileType, SDL_Texture*> *Graphics::loadAllTextures()
{
    std::map<TileType, SDL_Texture*> *texturesMap = new std::map<TileType, SDL_Texture*>();
    for (auto currentTileType : tileTypeVector)
    {
        (*texturesMap)[currentTileType] = loadTexture(getImagePathStringByTileType(currentTileType));
    }
    return texturesMap;
}

void Graphics::destroyAllTextures (std::map<TileType, SDL_Texture*> *texturesMap)
{
    std::map<TileType, SDL_Texture*>::iterator it = texturesMap->begin();
    while (it != texturesMap->end())
    {
        SDL_DestroyTexture(it->second);
    }
    texturesMap->clear();
    delete texturesMap;

}

void Graphics::destroyRectAndTexture (RectAndTexture *rectAndTexture) {
    delete rectAndTexture->rect;
    SDL_DestroyTexture(rectAndTexture->texture);
}

void Graphics::quitSdl()
{
    IMG_Quit();
    SDL_Quit();
}

Graphics::~Graphics()
{
    printf("Graphics destructor\n");
    quitSdl();
}
