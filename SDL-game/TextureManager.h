#ifndef __TextureManager__
#define __TextureManager__

#include "SDL.h"
#include <string>
#include <map>



class TextureManager {
public:
	static TextureManager& Instance()
	{
		static TextureManager instance; // Guaranteed to be destroyed
		return instance; // Instantiated on first use.
	}
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager() {}

	std::map<std::string, SDL_Texture*> m_textureMap;
};
#endif /* defined(__TextureManager__) */