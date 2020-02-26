#include "Graphics.h"

Graphics::Graphics(unsigned short int windowWidth, unsigned short int windowHeight, int flags)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _flags = flags;
    if (initializeSdl()) {
        _window = createWindow();
        _renderer = createRenderer();
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

SDL_Window *Graphics::createWindow() const
{

    SDL_Window *window = SDL_CreateWindow("InvasiveSpecies",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          _windowWidth, _windowHeight,
                                          _flags);
    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    return window;
}

SDL_Renderer *Graphics::createRenderer() const
{
    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED |
                          SDL_RENDERER_PRESENTVSYNC |
                          SDL_RENDERER_TARGETTEXTURE;

    SDL_Renderer *renderer = SDL_CreateRenderer(_window, -1, render_flags);
    if (!renderer)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return NULL;
    }

    return renderer;
}

void Graphics::fpsCounterLoop(Uint32 *startclock, Uint32 *deltaclock, Uint32 *currentFPS) const
{
    *deltaclock = SDL_GetTicks() - *startclock;
    if (*deltaclock != 0)
    {
        *currentFPS = 1000 / *deltaclock;
        printf("FPS:%d\n", *currentFPS);
    }
}

void Graphics::quitSdl() const
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

Graphics::~Graphics() 
{ 
    printf("Graphics destructor\n");
    quitSdl();
} 
