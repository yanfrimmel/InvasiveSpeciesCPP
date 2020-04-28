#pragma once

#include "Common.h"

#define FONT_SIZE 12

class Graphics {
private:
	Uint32 _windowWidth;
	Uint32 _windowHeight;
	Uint32 _flags;
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window;
	std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> _renderer;
	std::unique_ptr<std::map<TileType, SDL_Texture *>,
		std::function<void(std::map<TileType, SDL_Texture *> *)>>
		_textures;
	std::unique_ptr<RectAndTexture, std::function<void(RectAndTexture *)>>
		_baseTile;
	std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> _globalFont;

	static auto destroyAllTextures(std::map<TileType, SDL_Texture *> *texturesMap)
		-> void;
	static auto destroyRectAndTexture(RectAndTexture *rectAndTexture) -> void;
	static auto destroyFont(TTF_Font *font) -> void;
	static auto getImagePathStringByTileType(TileType tileType) -> const char *;
	static auto initializeSdl() -> bool;
	auto createWindow()->SDL_Window *;
	auto createRenderer()->SDL_Renderer *;
	auto loadAllTextures()->std::map<TileType, SDL_Texture *> *;
	static auto createRectFromTexture(SDL_Texture *texture)->RectAndTexture *;
	auto loadTexture(const char *imagePath)->SDL_Texture *;
	auto renderTexture(RectAndTexture *rectAndTexture) -> void;
	auto renderGameObjects(const std::vector<std::pair<TileType, SDL_Rect>> &gameObjectsPositionsMap) -> void;
	auto renderGridBackground() -> void; // render background image under game objects
	auto createBaseRect()->RectAndTexture *;
	static auto getFontFromFile(const char *file, int ptsize)->TTF_Font *;
	static auto createRegularFont()->TTF_Font *;
	auto quitSdl() -> void;

public:
	Graphics(Uint32 windowWidth = 800, Uint32 windowHeight = 600,
		Uint32 flags = 0);
	auto getWindowWidth() const { return _windowWidth; }
	auto getWindowHeight() const { return _windowHeight; }
	auto renderGrid(const std::vector<std::pair<TileType, SDL_Rect>>
		&gameObjectsPositionsVector) -> void;
	auto renderText(const std::string &textureText, SDL_Color textColor, int x,
		int y) -> void;
	auto clearRender() -> void;
	auto presentRender() -> void;
	~Graphics();
};
