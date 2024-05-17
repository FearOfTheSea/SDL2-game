#pragma once

#include <SDL.h>
#include "Game.h"
#include <vector>
#include "GamePlay.h"
#include <random>
#include <iostream>

void generateMapData(std::array<std::array<int, 25>, 25>& base)
{
	std::mt19937 randomNumGenerator{ std::random_device{}() };
	std::uniform_int_distribution<int> distribute{ 0, 9 };

	for (int y{}; y < 25; y++)
	{
		for (int x{}; x < 25; x++)
		{
			base[x][y] = distribute(randomNumGenerator);
			std::cout << base[x][y] << " ";
		}
		std::cout << '\n';
	}
}
GamePlay::GamePlay()
{
	generateMapData(mapData);
	run();
}
GamePlay::~GamePlay()
{
}
void GamePlay::run()
{
	SDL_Event event;
	while (true)
	{
		render();
		if (!handleEvent(event))
			break;
	}
	SDL_Quit();
}
void GamePlay::render()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Draw a white rectangle
	SDL_Rect rect = { 100, 100, 200, 150 };
	SDL_RenderFillRect(renderer, &rect);

	// Update the screen with the rendering performed
	SDL_RenderPresent(renderer);
	return;
}
bool GamePlay::handleEvent(SDL_Event& event)
{
	return true;
}