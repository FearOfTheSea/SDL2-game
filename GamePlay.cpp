#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include <array>
#include "GamePlay.h"
#include <random>
#include <iostream>
#include <type_traits>
#include <set>
#include <SDL_ttf.h>
#include "Unit.h"
#include <utility>
#include <cstring>

static void generateMapData(std::array<std::array<int, 25>, 25>& base)
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

static void generateCityData(std::array<std::array<GamePlay::city, 25>, 25>& base, Game::difficulty difficulty)
{
    // Initialize the entire map with none
    for (int row{}; row < 25; ++row)
    {
        for (int col{}; col < 25; ++col)
        {
            base[row][col] = GamePlay::city::none;
        }
    }

    int numNeutralCities{};
    switch (difficulty) {
    case Game::difficulty::easy:
        numNeutralCities = 8;
        break;
    case Game::difficulty::normal:
        numNeutralCities = 9;
        break;
    case Game::difficulty::hard:
        numNeutralCities = 10;
        break;
    }

    // Seed the random number generator with a random device
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int quadrant{}; quadrant < 4; ++quadrant) 
    {
        int startRow = quadrant / 2 * 12;
        int endRow = startRow + 11;
        int startCol = quadrant % 2 * 12;
        int endCol = startCol + 11;

        for (int i = 0; i < numNeutralCities; ++i)
        {
            std::uniform_int_distribution<> distRow(startRow, endRow);
            std::uniform_int_distribution<> distCol(startCol, endCol);
            int row = distRow(gen);
            int col = distCol(gen);
            base[row][col] = GamePlay::city::neutralCity;
        }
    }

    std::uniform_int_distribution<> distAllyRow(0, 11);
    std::uniform_int_distribution<> distAllyCol(0, 11);
    int allyRow = distAllyRow(gen);
    int allyCol = distAllyCol(gen);
    int allyQuadrant = (allyRow / 12) * 2 + (allyCol / 12);
    base[allyRow][allyCol] = GamePlay::city::allyCity;

    // Declare uniform distributions outside the switch statement
    std::uniform_int_distribution<> distEnemyRow;
    std::uniform_int_distribution<> distEnemyCol;
    std::uniform_int_distribution<> distNormalRow1;
    std::uniform_int_distribution<> distNormalCol1;
    std::uniform_int_distribution<> distNormalRow2;
    std::uniform_int_distribution<> distNormalCol2;
    std::uniform_int_distribution<> distHardRow1;
    std::uniform_int_distribution<> distHardCol1;
    std::uniform_int_distribution<> distHardRow2;
    std::uniform_int_distribution<> distHardCol2;
    std::uniform_int_distribution<> distHardRow3;
    std::uniform_int_distribution<> distHardCol3;

    // Generate enemy cities based on difficulty
    switch (difficulty)
    {
    case Game::difficulty::easy:
        do {
            distEnemyRow = std::uniform_int_distribution<>(13, 24);
            distEnemyCol = std::uniform_int_distribution<>(13, 24);
        } while ((distEnemyRow(gen) / 12) * 2 + (distEnemyCol(gen) / 12) == allyQuadrant);
        base[distEnemyRow(gen)][distEnemyCol(gen)] = GamePlay::city::enemyCity;
        break;
    case Game::difficulty::normal:
        do {
            distNormalRow1 = std::uniform_int_distribution<>(13, 24);
            distNormalCol1 = std::uniform_int_distribution<>(0, 11);
        } while ((distNormalRow1(gen) / 12) * 2 + (distNormalCol1(gen) / 12) == allyQuadrant);
        base[distNormalRow1(gen)][distNormalCol1(gen)] = GamePlay::city::enemyCity;

        do {
            distNormalRow2 = std::uniform_int_distribution<>(0, 11);
            distNormalCol2 = std::uniform_int_distribution<>(13, 24);
        } while ((distNormalRow2(gen) / 12) * 2 + (distNormalCol2(gen) / 12) == allyQuadrant);
        base[distNormalRow2(gen)][distNormalCol2(gen)] = GamePlay::city::enemyCity;
        break;
    case Game::difficulty::hard:
        do {
            distHardRow1 = std::uniform_int_distribution<>(12, 24);
            distHardCol1 = std::uniform_int_distribution<>(0, 11);
        } while ((distHardRow1(gen) / 12) * 2 + (distHardCol1(gen) / 12) == allyQuadrant);
        base[distHardRow1(gen)][distHardCol1(gen)] = GamePlay::city::enemyCity;

        do {
            distHardRow2 = std::uniform_int_distribution<>(0, 11);
            distHardCol2 = std::uniform_int_distribution<>(13, 24);
        } while ((distHardRow2(gen) / 12) * 2 + (distHardCol2(gen) / 12) == allyQuadrant);
        base[distHardRow2(gen)][distHardCol2(gen)] = GamePlay::city::enemyCity;

        do {
            distHardRow3 = std::uniform_int_distribution<>(13, 24);
            distHardCol3 = std::uniform_int_distribution<>(13, 24);
        } while ((distHardRow3(gen) / 12) * 2 + (distHardCol3(gen) / 12) == allyQuadrant);
        base[distHardRow3(gen)][distHardCol3(gen)] = GamePlay::city::enemyCity;
        break;
    }


    // Output the 2D array as integer values
    for (int row{ 0 }; row < 25; ++row)
    {
        for (int col{ 0 }; col < 25; ++col)
        {
            std::cout << static_cast<int>(base[row][col]) << " ";
        }
        std::cout << std::endl;
    }
}

enum class terrain { grass0, grass1, desert2, desert3, jungle4, jungle5, mountain6, mountain7, water8 };

static std::array<SDL_Texture*, 9> loadTerrainTextures(SDL_Renderer* renderer) 
{
	std::array<SDL_Texture*, 9> textures{};
	textures[static_cast<int>(terrain::grass0)] = IMG_LoadTexture(renderer, "assets/grass0.png");
	textures[static_cast<int>(terrain::grass1)] = IMG_LoadTexture(renderer, "assets/grass1.png");
	textures[static_cast<int>(terrain::desert2)] = IMG_LoadTexture(renderer, "assets/desert2.png");
	textures[static_cast<int>(terrain::desert3)] = IMG_LoadTexture(renderer, "assets/desert3.png");
	textures[static_cast<int>(terrain::jungle4)] = IMG_LoadTexture(renderer, "assets/jungle4.png");
	textures[static_cast<int>(terrain::jungle5)] = IMG_LoadTexture(renderer, "assets/jungle5.png");
	textures[static_cast<int>(terrain::mountain6)] = IMG_LoadTexture(renderer, "assets/mountain6.png");
	textures[static_cast<int>(terrain::mountain7)] = IMG_LoadTexture(renderer, "assets/mountain7.png");
	textures[static_cast<int>(terrain::water8)] = IMG_LoadTexture(renderer, "assets/water8.png");
	return textures;
}
static std::array<SDL_Texture*, 3> loadCityTextures(SDL_Renderer* renderer)
{
	std::array<SDL_Texture*, 3> textures{};
    textures[static_cast<int>(GamePlay::city::allyCity)] = IMG_LoadTexture(renderer, "assets/allyCity.png");
    textures[static_cast<int>(GamePlay::city::enemyCity)] = IMG_LoadTexture(renderer, "assets/enemyCity.png");
    textures[static_cast<int>(GamePlay::city::neutralCity)] = IMG_LoadTexture(renderer, "assets/neutralCity.png");
	return textures;
}
GamePlay::GamePlay()
    : resources{ 500 }
    , turn{ 1 }
{
	generateMapData(mapData);
    generateCityData(cityData, getDifficulty());
	loadAssets();
    gameCreateUnit();
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

void GamePlay::renderTerrainInfo()
{
    const char* s = nullptr;
    switch (mapData[x][y])
    {
    case 0:
    case 1:
        s = "Terrain type: Plain \nUnits gain 50% \nattacking bonus!\nUnits lose 50%\nless supply!";
        break;
    case 2:
    case 3:
        s = "Terrain type: Desert\nUnits gain 100% \nattacking bonus!\nUnits lose 50%\nmore supply!";
        break;
    case 4:
    case 5:
        s = "Terrain type: Jungle\nUnits gain 50% \ndefensive bonus!\nUnits lose 50%\nless supply!";
        break;
    case 6:
    case 7:
        s = "Terrain type: Mountain\nUnits gain 100% \ndefensive bonus!\nUnits lose 50%\nmore supply!";
        break;
    case 8:
        s = "Terrain type: Water\nUnits cannot move\nin here!";
        break;
    default:
        s = "abc";
        break;
    }
    SDL_Color textColor = { 255, 255, 255 }; 
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, s, textColor, 450);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textBox = { 815, 50, textWidth, textHeight };

    SDL_RenderCopy(renderer, textTexture, nullptr, &textBox);
    SDL_DestroyTexture(textTexture);
}

Unit* existsWithValues(const std::vector<Unit*>& vec, int a, int b) {
    for (const Unit* instance : vec) {
        if (instance && instance->getX() == a && instance->getY() == b) {
            return const_cast<Unit*>(instance);
        }
    }
    return nullptr;
}
void GamePlay::renderUnitInfo()
{
    Unit* temp = existsWithValues(allUnits, x, y);
    const char* s = nullptr;
    std::string result{ "This unit is an " };
    if (temp == nullptr)
    {
        s = "No units here!";
    }
    else
    {
        result += (temp->getUnitType() == 1 ? "Ally\n" : "Enemy\n");
        result += ("The Unit has:\n");
        result += (std::to_string(temp->getAttack()));
        result += (" Attack\n");
        result += (std::to_string(temp->getDefense()));
        result += (" Defense\n");
        result += (std::to_string(temp->getSupply()));
        result += (" Supply\n");
        s = result.c_str();
    }
    
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, s, textColor, 450);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textBox = { 815, 350, textWidth, textHeight };

    SDL_RenderCopy(renderer, textTexture, nullptr, &textBox);
    SDL_DestroyTexture(textTexture);
}

void GamePlay::render() 
{
	SDL_RenderClear(renderer);

	const int tileSize = 32;

	for (int row = 0; row < mapData.size(); ++row) {
		for (int col = 0; col < mapData[row].size(); ++col) {
			int terrainType = mapData[col][row];
            int cityType = static_cast<int> (cityData[col][row]);
            if ((cityType != static_cast<int> (GamePlay::city::none)) && terrainType == static_cast<int> (GamePlay::terrain::water8))
            {
                mapData[col][row] = static_cast<int> (GamePlay::terrain::grass0);
            }
			SDL_Rect terrainRectangle = { col * tileSize, row * tileSize, tileSize, tileSize };
			SDL_RenderCopy(renderer, terrainTextures[terrainType], nullptr, &terrainRectangle);
            if (cityType == static_cast<int> (GamePlay::city::none))
            {
                continue;
            }
            SDL_Rect cityRectangle = { col * tileSize, row * tileSize, tileSize, tileSize };
            SDL_RenderCopy(renderer, cityTextures[cityType], nullptr, &cityRectangle);
		}
	}
    
    SDL_Rect selectRectangle = { x * tileSize, y * tileSize, tileSize, tileSize };
    SDL_RenderCopy(renderer, selectTexture, nullptr, &selectRectangle);

    SDL_Rect UIRectangle = { 800, 0, 400, 800 };
    SDL_RenderCopy(renderer, UITexture, nullptr, &UIRectangle);

    for (const auto& pUnit : allUnits)
    {
        if (pUnit->getUnitType() == 1)
        {
            SDL_Rect unitRectangle = { pUnit->getX() * tileSize, pUnit->getY() * tileSize, tileSize, tileSize };
            SDL_RenderCopy(renderer, allyUnitTexture, nullptr, &unitRectangle);
        }
        else
        {
            SDL_Rect unitRectangle = { pUnit->getX() * tileSize, pUnit->getY() * tileSize, tileSize, tileSize };
            SDL_RenderCopy(renderer, enemyUnitTexture, nullptr, &unitRectangle);
        }
    }
    renderTerrainInfo();
    renderUnitInfo();

	SDL_RenderPresent(renderer);
}
bool GamePlay::handleEvent(SDL_Event& event)
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                if (y > 0) y--;
                return true;
            case SDLK_DOWN:
                if (y < 24) y++;
                return true;
            case SDLK_RIGHT:
                if (x < 24) x++;
                return true;
            case SDLK_LEFT:
                if (x > 0) x--;
                return true;
            default:
                return true;
            }
        default:
            return true;
        }
        return true;
    }
    return true;
}
void GamePlay::loadAssets()
{
	terrainTextures = loadTerrainTextures(renderer);
	cityTextures = loadCityTextures(renderer);
    selectTexture = IMG_LoadTexture(renderer, "assets/select.png");
    UITexture = IMG_LoadTexture(renderer, "assets/ui.png");
    font = TTF_OpenFont("assets/font.ttf", 28);
    allyUnitTexture = IMG_LoadTexture(renderer, "assets/allyUnit.png");
    enemyUnitTexture = IMG_LoadTexture(renderer, "assets/enemyUnit.png");
}
void GamePlay::gameCreateUnit()
{
    for (int j{}; j < 25; ++j)
    {
        for (int i{}; i < 25; ++i)
        {
            if (cityData[i][j] == city::allyCity)
            {
                allUnits.push_back(new AllyUnit(i, j));
            }
            else if (cityData[i][j] == city::enemyCity)
            {
                allUnits.push_back(new EnemyUnit(i, j));
            }
        }
    }
}

