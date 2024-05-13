#pragma once

#include <SDL.h>
#include "tile.h"

class InputHandler
{
public:
	InputHandler() = default;
	InputHandler(HighlightedTile* highlightedTile) : highlightedTile(highlightedTile) {}
	bool handleEvent();
private:
	HighlightedTile* highlightedTile;
};
