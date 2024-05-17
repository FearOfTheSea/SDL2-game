#pragma once

#include <SDL.h>
#include "Game.h"
#include <vector>
class GamePlay : public Game
{
public:
	GamePlay();
	~GamePlay();
	enum class terrain{ grass0, grass1, jungle2, jungle3, desert4, desert5, desert6, mountain7, mountain8, water9 };
private:
	void run() override;
	void render() override;
	bool handleEvent(SDL_Event& event) override;
	SDL_Renderer* renderer{ getRenderer() };
	SDL_Window* window{ getWindow() };
	
	std::vector<std::vector<int>> mapData;

	//std::vector<std::vector<Unit>> unitData;
	//std::vector<std::vector<Structure>> structureData;
	//static int turn;

	int x;
	int y;
};