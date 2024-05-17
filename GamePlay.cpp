#pragma once

#include <SDL.h>
#include "Game.h"
#include <vector>
#include "GamePlay.h"
#include <random>
#include <iostream>

void generateMapData(std::vector<std::vector<int>>& base)
{
	base.resize(25);
	for (auto& row : base)
	{
		row.resize(25);
	}
	std::mt19937 randomNumGenerator{};
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
	return;
}
bool GamePlay::handleEvent(SDL_Event& event)
{
	return true;
}