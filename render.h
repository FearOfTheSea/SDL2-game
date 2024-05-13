//render.h

#pragma once

#include <SDL.h>
#include "environment.h"
#include "map.h"
#include "tile.h"

class Render
{
public:
	Render(SDL_Renderer* renderer, const Map& map, Environment& environment, HighlightedTile& highlightedTile);
	~Render();
	void RenderScreen();
private:
	SDL_Renderer* renderer;
	void clear();
	void present();
	void renderEnvironment();
	void renderHighlightedTile();
	const Map& map;
	const Environment& environment;
	HighlightedTile& highlightedTile;
};
