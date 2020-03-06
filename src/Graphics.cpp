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

void Graphics::quitSdl()
{
    _renderer.reset(nullptr);
    _window.reset(nullptr);
    SDL_Quit();
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

void Graphics::renderTexture(RectAndTexture rectAndTexture)
{
  SDL_RenderCopy(_renderer.get(), rectAndTexture.texture, NULL, rectAndTexture.rect);
}

RectAndTexture Graphics::createRectAndTexture(SDL_Texture *texture)
{
    SDL_Rect *dest = new SDL_Rect();
    SDL_QueryTexture(texture, NULL, NULL, &dest->w, &dest->h);
    RectAndTexture rectAndTexture = {dest, texture};
    return rectAndTexture;
}

Graphics::~Graphics()
{
    printf("Graphics destructor\n");
    quitSdl();
}
