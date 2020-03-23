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
    std::unique_ptr<std::map<TileType, SDL_Texture*>, std::function<void(std::map<TileType, SDL_Texture*> *)>> _textures;
    std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>> _baseTile;
    std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> _globalFont;

    static void destroyAllTextures (std::map<TileType, SDL_Texture*> *texturesMap);
    static void destroyRectAndTexture (RectAndTexture *rectAndTexture);
    static void destroyFont(TTF_Font * font);
    static const char* getImagePathStringByTileType(TileType tileType); 
    bool initializeSdl() const;
    SDL_Window *createWindow() ;
    SDL_Renderer *createRenderer() ;
    std::map<TileType, SDL_Texture*> *loadAllTextures();
    RectAndTexture *createRectFromTexture(SDL_Texture *texture);
    SDL_Texture *loadTexture(const char *imagePath);
    void renderTexture(RectAndTexture *rectAndTexture);
    void renderGridBackground(RectAndTexture *baseTile);
    RectAndTexture *createBaseRect();
    TTF_Font * getFontFromFile(const char *file, int ptsize);
    TTF_Font * createRegularFont();
    void quitSdl();

public:
    Graphics(unsigned short int windowWidth = 800, unsigned short int windowHeight = 600, Uint32 flags = 0);
    int getWindowWidth() const { return _windowWidth; }
    int getWindowHeight() const { return _windowHeight; }
    void renderGrid(std::map<TileType, std::vector<SDL_Rect>> *tilesPositionsMap);
    void renderText(std::string textureText, SDL_Color textColor, int x, int y);
    void clearRender();
    void presentRender();
    ~Graphics();
};

#endif
