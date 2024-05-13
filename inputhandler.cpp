#include "inputhandler.h"
#include "tile.h"
#include <iostream>


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
			highlightedTile->changeHighlightedTile(event);
			break;
		}
	}
	return true;
}
