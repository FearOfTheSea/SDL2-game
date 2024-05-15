#pragma once

#include <SDL.h>
#include "tile.h"
#include "turncounter.h"
class InputHandler
{
public:
	InputHandler() = default;
	InputHandler(HighlightedTile* highlightedTile, TurnCounter* turnCounter) : highlightedTile(highlightedTile), turnCounter(turnCounter) {}
	bool handleEvent();
private:
	HighlightedTile* highlightedTile;
	TurnCounter* turnCounter;
};
