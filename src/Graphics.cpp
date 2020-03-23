#include "Graphics.h"

Graphics::Graphics(unsigned short int windowWidth, unsigned short int windowHeight, Uint32 flags)
    : _windowWidth{windowWidth}, _windowHeight{windowHeight}, _flags{flags}
{
    if (initializeSdl())
    {
        _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
                      createWindow(),
                      SDL_DestroyWindow);
        _renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>(
                        createRenderer(),
                        SDL_DestroyRenderer);
        _textures = std::unique_ptr<std::map<TileType, SDL_Texture *>,
        std::function<void(std::map<TileType, SDL_Texture *> *)>>(
            loadAllTextures(),
            Graphics::destroyAllTextures);
        _baseTile = std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>>(
                        createBaseRect(),
                        destroyRectAndTexture);
        _globalFont = std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>>(
                          createRegularFont(),
                          destroyFont);
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
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("could not initialize sdl2_image: %s\n", IMG_GetError());
        return false;
    }
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

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

void Graphics::clearRender()
{
    SDL_RenderClear(_renderer.get());
}

void Graphics::presentRender()
{
    SDL_RenderPresent(_renderer.get());
}

void Graphics::renderGrid(std::map<TileType, std::vector<SDL_Rect>> *tilesPositionsMap)
{
    // printf("renderGrid\n");
    renderGridBackground(_baseTile.get());
}

void Graphics::renderGridBackground(RectAndTexture *baseTile)
{
    // printf("renderGridBackground\n");
    int tileWidth = baseTile->rect->w;
    int tileHeight = baseTile->rect->h;
    _baseTile->texture = (*_textures.get())[SOIL];
    for (int i = 0; i < _windowWidth; i += tileWidth)
    {
        for (int j = 0; j < _windowHeight; j += tileHeight)
        {
            renderTexture(baseTile);
            baseTile->rect->x = i;
            baseTile->rect->y = j;
        }
    }
}

void Graphics::renderTexture(RectAndTexture *rectAndTexture)
{
    SDL_RenderCopy(_renderer.get(), rectAndTexture->texture, NULL, rectAndTexture->rect);
}

const char *Graphics::getImagePathStringByTileType(TileType tileType)
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
    default:
        break;
    }
    return nullptr;
}

std::map<TileType, SDL_Texture *> *Graphics::loadAllTextures()
{
    std::map<TileType, SDL_Texture *> *texturesMap = new std::map<TileType, SDL_Texture *>();
    for (auto currentTileType : tileTypeVector)
    {
        (*texturesMap)[currentTileType] = loadTexture(getImagePathStringByTileType(currentTileType));
    }
    return texturesMap;
}

void Graphics::destroyAllTextures(std::map<TileType, SDL_Texture *> *texturesMap)
{

    for (auto const& p : *texturesMap)
    {
        SDL_DestroyTexture(p.second);
    }

    texturesMap->clear();
    delete texturesMap;
    printf("destroyAllTextures done\n");
}

void Graphics::destroyFont(TTF_Font * font)
{
    TTF_CloseFont(font);
    printf("destroyFont done\n");
}

void Graphics::destroyRectAndTexture(RectAndTexture *rectAndTexture)
{
    delete rectAndTexture->rect;
    SDL_DestroyTexture(rectAndTexture->texture);
    delete rectAndTexture;
}


void Graphics::renderText(std::string textureText, SDL_Color textColor, int x, int y)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(_globalFont.get(), textureText.c_str(), textColor);
    SDL_Texture* textTexture = nullptr;
    if ( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(_renderer.get(), textSurface );
        if ( textTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            // int mWidth = textSurface->w;
            // int mHeight = textSurface->h;
            std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>> baseTile =
                        std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>>(
                            createRectFromTexture(textTexture),
                            destroyRectAndTexture);
            baseTile->rect->x = x;
            baseTile->rect->y = y;
            renderTexture(baseTile.get());
            baseTile.reset();
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
}

TTF_Font *Graphics::getFontFromFile(const char *file, int ptsize)
{
    TTF_Font *gFont = TTF_OpenFont(file, ptsize);

    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    return gFont;
}


TTF_Font *Graphics::createRegularFont()
{
    return getFontFromFile(FONT_PATH, 20);
}

void Graphics::quitSdl()
{
    // these must be here or else they will get called after SDL_Quit()
    _globalFont.reset();
    _baseTile.reset();
    _textures.reset();
    _renderer.reset();
    _window.reset();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Graphics::~Graphics()
{
    printf("Graphics destructor\n");
    quitSdl();
}
