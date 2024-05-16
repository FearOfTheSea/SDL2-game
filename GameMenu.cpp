#include "GameMenu.h"
#include <iostream>
SDL_Texture* getTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* surface{ SDL_LoadBMP(path) };
	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer, surface) };
	SDL_FreeSurface(surface);
	return texture;
}

GameMenu::GameMenu()
{
	run();
}

void GameMenu::run()
{
	if (!renderer) std::cout << "a";
	SDL_Event event;
	while (true)
	{
		if (!handleEvent(event))
		{
			break;
		}
		render();
	}
	nextGameState();
}

void GameMenu::render()
{
	SDL_RenderClear(renderer);

	SDL_Texture* difficultyEasyTexture{ getTexture(renderer, "assets/EASY.bmp") };
	SDL_Rect easyRectangle{ 270, 300, 260, 40 };
	SDL_RenderCopy(renderer, difficultyEasyTexture, nullptr, &easyRectangle);

	SDL_Texture* difficultyNormalTexture{ getTexture(renderer, "assets/NORMAL.bmp") };
	SDL_Rect normalRectangle{ 270, 450, 260, 40 };
	SDL_RenderCopy(renderer, difficultyNormalTexture, nullptr, &normalRectangle);

	SDL_Texture* difficultyHardTexture{ getTexture(renderer, "assets/HARD.bmp") };
	SDL_Rect hardRectangle{ 270, 600, 260, 40 };
	SDL_RenderCopy(renderer, difficultyHardTexture, nullptr, &hardRectangle);

	SDL_RenderPresent(renderer);
}

bool GameMenu::handleEvent(SDL_Event& event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_0)
			return false;
	}
	return true;
}

void GameMenu::nextGameState() {}