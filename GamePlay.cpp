#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include <vector>
#include "GamePlay.h"
#include <random>
#include <iostream>

void generateMapData(std::array<std::array<int, 25>, 25>& base)
{
	std::mt19937 randomNumGenerator{ std::random_device{}() };
	std::uniform_int_distribution<int> distribute{ 0, 8 };

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
enum class terrain { grass0, grass1, desert2, desert3, jungle4, jungle5, mountain6, mountain7, water8 };

std::array<SDL_Texture*, 10> loadTerrainTextures(SDL_Renderer* renderer) 
{
	std::array<SDL_Texture*, 10> textures;
	textures[static_cast<int>(terrain::grass0)] = IMG_LoadTexture(renderer, "assets/grass0.png");
	textures[static_cast<int>(terrain::grass1)] = IMG_LoadTexture(renderer, "assets/grass1.png");
	textures[static_cast<int>(terrain::desert2)] = IMG_LoadTexture(renderer, "assets/desert2.png");
	textures[static_cast<int>(terrain::desert3)] = IMG_LoadTexture(renderer, "assets/desert3.png");
	textures[static_cast<int>(terrain::jungle4)] = IMG_LoadTexture(renderer, "assets/jungle4.png");
	textures[static_cast<int>(terrain::jungle5)] = IMG_LoadTexture(renderer, "assets/jungle5.png");
	textures[static_cast<int>(terrain::mountain6)] = IMG_LoadTexture(renderer, "assets/mountain6.png");
	textures[static_cast<int>(terrain::mountain7)] = IMG_LoadTexture(renderer, "assets/mountain7.png");
	textures[static_cast<int>(terrain::water8)] = IMG_LoadTexture(renderer, "assets/water8.png");

	for (auto& texture : textures) {
		if (texture == nullptr) {
			std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
		}
	}

	return textures;
}
GamePlay::GamePlay()
{
	generateMapData(mapData);
	loadAssets();
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

	const int tileSize = 32;

	for (int row = 0; row < mapData.size(); ++row) {
		for (int col = 0; col < mapData[row].size(); ++col) {
			int terrainType = mapData[row][col];
			SDL_Rect destRect = { col * tileSize, row * tileSize, tileSize, tileSize };

			SDL_RenderCopy(renderer, terrainTextures[terrainType], nullptr, &destRect);
		}
	}

	SDL_RenderPresent(renderer);
}
bool GamePlay::handleEvent(SDL_Event& event)
{
	return true;
}
void GamePlay::loadAssets()
{
	terrainTextures = loadTerrainTextures(renderer);
}