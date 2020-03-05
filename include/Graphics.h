#ifndef GRAPHICS_H /* Include guard */
#define GRAPHICS_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_error.h>
#include <memory>
#include <functional>

class Graphics
{
private:
    unsigned short int _windowWidth;
    unsigned short int _windowHeight;
    int _flags;
    unsigned short int _fpsCap;
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> _renderer;

    bool initializeSdl() const;
    SDL_Window *createWindow() ;
    SDL_Renderer *createRenderer() ;
    void quitSdl();

public:
    struct RectAndTexture
    {
        SDL_Rect *rect;
        SDL_Texture *texture;
    };
    Graphics(unsigned short int windowWidth = 800, unsigned short int windowHeight = 600, int flags = 0, unsigned short int fpsCap = 60);
    void fpsCounterLoop(Uint32 *startclock, Uint32 *deltaclock, Uint32 *currentFPS) const;
    int getWindowWidth() const { return _windowWidth; }
    int getWindowHeight() const { return _windowHeight; }
    RectAndTexture createRectAndTexture(SDL_Texture *texture);
    SDL_Texture *loadTexture(const char *imagePath);
    void renderTexture(RectAndTexture rectAndTexture);
    unsigned short int getFpsCap(); 
    ~Graphics();
};

#endif
