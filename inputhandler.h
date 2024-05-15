#pragma once

#include <SDL.h>
#include "tile.h"
#include "turncounter.h"
#include "unit.h"

class InputHandler
{
public:
	InputHandler() = default;
	InputHandler(HighlightedTile* highlightedTile, TurnCounter* turnCounter, Warrior* warrior) : highlightedTile(highlightedTile), turnCounter(turnCounter) 
		, warrior(warrior) {}
	bool handleEvent();
private:
	HighlightedTile* highlightedTile;
	TurnCounter* turnCounter;
	Warrior* warrior;
};
