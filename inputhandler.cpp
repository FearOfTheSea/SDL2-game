#include "inputhandler.h"
#include "tile.h"
#include <iostream>
#include "unit.h"

bool InputHandler::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				turnCounter->increment();
				std::cout << turnCounter->getTurn() << " ";

			}
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_a
				|| event.key.keysym.sym == SDLK_d)
			{
				warrior->moveUnit(event);
			}
			highlightedTile->changeHighlightedTile(event);
			break;
		}
	}
	return true;
}
