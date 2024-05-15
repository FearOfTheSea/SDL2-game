#include "unit.h"
#include <iostream>
void Unit::moveUnit(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		y--;
		break;
	case SDLK_s:
		y++;
		break;
	case SDLK_a:
		x--;
		break;
	case SDLK_d:
		x++;
		break;
		default:
		break;
	}
	if (x < 0) x = 0;
	if (x > 25) x = 25;
	if (y < 0) y = 0;
	if (y > 25) y = 25;
	std::cout << x << " " << y << " ";
}