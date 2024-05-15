//render.h

#pragma once

#include <SDL.h>
#include "environment.h"
#include "map.h"
#include "tile.h"
#include "turncounter.h"
#include <SDL_ttf.h>
#include "inputhandler.h"
#include "vector"
#include "unit.h"

class Render
{
public:
	Render(SDL_Renderer* renderer, const Map& map, Environment& environment, HighlightedTile& highlightedTile, TurnCounter& turnCounter, TTF_Font* font, InputHandler* inputHandler
		, Warrior* warrior);
	~Render();
	void RenderScreen();
private:
	SDL_Renderer* renderer;
	void clear();
	void present();
	void renderEnvironment();
	void renderHighlightedTile();
	void renderUI(int turn);
	void renderStuctures(int x, int y);
	void renderWarrior();
	void renderVictory();
	const Map& map;
	const Environment& environment;
	HighlightedTile& highlightedTile;
	TurnCounter& turnCounter;
	InputHandler* inputHandler;
	TTF_Font* font;
	Warrior* warrior;
};

