//game.h

#pragma once

#include "SDL.h"
#include "map.h"
#include "render.h"
#include "environment.h"
#include "inputhandler.h"
#include "tile.h"
#include <SDL.h>

class Game
{
public:
	Game();
	void run();
	void close();
private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	Render* render{ nullptr };
	Map map;
	Environment environment;
	InputHandler inputHandler;
	HighlightedTile highlightedTile;
};