#pragma once

#include <SDL.h>
#include "Game.h"
#include <vector>
#include <array>
class GamePlay : public Game
{
public:
	GamePlay();
	~GamePlay();
	enum class terrain{ grass0, grass1, desert2, desert3, jungle4, jungle5, mountain6, mountain7, water8 };
private:
	void run() override;
	void render() override;
	bool handleEvent(SDL_Event& event) override;
	SDL_Renderer* renderer{ getRenderer() };
	SDL_Window* window{ getWindow() };
	
	std::array<std::array<int, 25>, 25> mapData;

	std::array<SDL_Texture*, 10> terrainTextures;
	void loadAssets();
	//std::vector<std::vector<Unit>> unitData;
	//std::vector<std::vector<Structure>> structureData;
	//static int turn;

	int x;
	int y;
};