#ifndef GRAPHICS_H /* Include guard */
#define GRAPHICS_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_error.h>

class Graphics
{
private:
    int _flags;
    unsigned short int _windowWidth;
    unsigned short int _windowHeight;
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    bool initializeSdl() const;
    SDL_Window *createWindow() const;
    SDL_Renderer *createRenderer() const;
    void quitSdl() const;

public:
    Graphics(unsigned short int windowWidth = 800, unsigned short int windowHeight = 600, int flags = 0);
    void fpsCounterLoop(Uint32 *startclock, Uint32 *deltaclock, Uint32 *currentFPS) const;
    int getWindowWidth() const { return _windowWidth; }
    int getWindowHeight() const { return _windowHeight; }
    ~Graphics();  
};

#endif