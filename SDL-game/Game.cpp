#include "Game.h"
#include <iostream>
#include <SDL_image.h>
#include <io.h>

typedef TextureManager TheTextureManager;

bool Game::init(
	const char* title,
	int xpos,
	int ypos,
	int width,
	int height,
	bool fullscreen)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
				if (!TheTextureManager::Instance().load("assets/ken.png", "ken", m_pRenderer)) 
				{
					return false; // cant' load file
				}
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully, start the main loop
	return true;
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::update() {
	m_currentFrame = int((SDL_GetTicks() / 100) % 10);
}

void Game::render() 
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
	TheTextureManager::Instance().draw("ken", 0, 0, 101, 120, m_pRenderer);
	TheTextureManager::Instance().drawFrame("ken", 100, 100, 101, 120, 1, m_currentFrame, m_pRenderer);
	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}