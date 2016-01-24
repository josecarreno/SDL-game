#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer * pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) 
	{
		std::cout << "TextureManager::load - Could not load " << fileName;
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// If everything went ok, add the texture to our map
	if (texture != 0) 
	{
		m_textureMap[id] = texture;
		return true;
	}

	// Reaching here means something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer,SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int
	width, int height, int currentRow, int currentFrame, SDL_Renderer
	*pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}