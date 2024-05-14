//render.h

#pragma once

#include <SDL.h>
#include "environment.h"
#include "map.h"
#include "tile.h"
#include "turncounter.h"
#include <SDL_ttf.h>
#include "inputhandler.h"

class Render
{
public:
	Render(SDL_Renderer* renderer, const Map& map, Environment& environment, HighlightedTile& highlightedTile, TurnCounter& turnCounter, TTF_Font* font, InputHandler* inputHandler);
	~Render();
	void RenderScreen();
private:
	SDL_Renderer* renderer;
	void clear();
	void present();
	void renderEnvironment();
	void renderHighlightedTile();
	void renderUI(int turn);
	const Map& map;
	const Environment& environment;
	HighlightedTile& highlightedTile;
	TurnCounter& turnCounter;
	InputHandler* inputHandler;
	TTF_Font* font;
};


