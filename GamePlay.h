#pragma once

#include <SDL.h>
#include "Game.h"
#include "Unit.h"
#include <vector>
#include <array>
#include <SDL_ttf.h>
#include <string>

class GamePlay : public Game
{
public:
	GamePlay();
	~GamePlay();
	enum class terrain{ grass0, grass1, desert2, desert3, jungle4, jungle5, mountain6, mountain7, water8 };
	enum class city{ neutralCity, allyCity, enemyCity, none };
private:
	void run() override;
	void render() override;
	bool handleEvent(SDL_Event& event) override;
	SDL_Renderer* renderer{ getRenderer() };
	SDL_Window* window{ getWindow() };
	
	std::array<std::array<int, 25>, 25> mapData;
	std::array<std::array<city, 25>, 25> cityData;

	std::array<SDL_Texture*, 9> terrainTextures;
	std::array<SDL_Texture*, 3> cityTextures;
	
	std::vector<Unit*> allUnits;
	void gameCreateUnit();
	//void commandCreateUnit();

	void renderTerrainInfo();
	void renderUnitInfo();

	SDL_Texture* selectTexture;
	SDL_Texture* UITexture;

	TTF_Font* font;
	void loadAssets();
	
	int x;
	int y;

	int resources;
	int turn;

	void endTurn();

	SDL_Texture* allyUnitTexture;
	SDL_Texture* enemyUnitTexture;
};