#include "GameMenu.h"
#include <iostream>
#include "GamePlay.h"
SDL_Texture* getTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* surface{ IMG_Load(path) };
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
	SDL_Event event;
	while (true)
	{
		render();
		if (!handleEvent(event))
		{
			break;
		}
	}
	SDL_RenderClear(renderer);
	GamePlay GamePlay;
}

void GameMenu::render()
{
	SDL_RenderClear(renderer);

	SDL_Texture* whiteTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 800);
	SDL_SetRenderTarget(renderer, whiteTexture);
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_SetRenderTarget(renderer, nullptr);
	
	SDL_Texture* difficultyEasyTexture{ getTexture(renderer, "assets/EASY.bmp") };
	SDL_Rect easyRectangle{ 270, 300, 260, 40 };
	SDL_RenderCopy(renderer, difficultyEasyTexture, nullptr, &easyRectangle);
	SDL_DestroyTexture(difficultyEasyTexture);

	SDL_Texture* difficultyNormalTexture{ getTexture(renderer, "assets/NORMAL.bmp") };
	SDL_Rect normalRectangle{ 270, 450, 260, 40 };
	SDL_RenderCopy(renderer, difficultyNormalTexture, nullptr, &normalRectangle);
	SDL_DestroyTexture(difficultyNormalTexture);

	SDL_Texture* difficultyHardTexture{ getTexture(renderer, "assets/HARD.bmp") };
	SDL_Rect hardRectangle{ 270, 600, 260, 40 };
	SDL_RenderCopy(renderer, difficultyHardTexture, nullptr, &hardRectangle);
	SDL_DestroyTexture(difficultyHardTexture);

	SDL_Texture* logoTexture{ getTexture(renderer, "assets/title.png") };
	SDL_Rect logoRectangle{ 120, 100, 560 ,58 };
	SDL_RenderCopy(renderer, logoTexture, nullptr, &logoRectangle);

	SDL_RenderPresent(renderer);
}

bool GameMenu::handleEvent(SDL_Event& event)
{
	while (SDL_PollEvent(&event))
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_0:
			setDifficulty(difficulty::easy);
			std::cout << "Chosen easy\n";
			return false;
		case SDLK_1:
			setDifficulty(difficulty::normal);
			std::cout << "Chosen normal\n";
			return false;
		case SDLK_2:
			setDifficulty(difficulty::hard);
			std::cout << "Chosen hard\n";
			return false;
		default:
			break;
		}
	}
	return true;
}

GameMenu::~GameMenu()
{
}