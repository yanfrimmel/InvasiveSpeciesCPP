#ifndef GRAPHICS_H /* Include guard */
#define GRAPHICS_H

#include "Common.h"

class Graphics
{
private:
    unsigned short int _windowWidth;
    unsigned short int _windowHeight;
    Uint32 _flags;
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> _renderer;

    bool initializeSdl() const;
    SDL_Window *createWindow() ;
    SDL_Renderer *createRenderer() ;
    void quitSdl();

public:
    Graphics(unsigned short int windowWidth = 800, unsigned short int windowHeight = 600, Uint32 flags = 0);
    Uint32 calculateFpsAndDelta(Uint32 *startclock, Uint32 *deltaclock) const;
    int getWindowWidth() const { return _windowWidth; }
    int getWindowHeight() const { return _windowHeight; }
    RectAndTexture createRectAndTexture(SDL_Texture *texture);
    SDL_Texture *loadTexture(const char *imagePath);
    void renderTexture(RectAndTexture rectAndTexture); 
    ~Graphics();
};

#endif
