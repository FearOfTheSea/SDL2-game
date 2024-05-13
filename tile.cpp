#include "tile.h"
#include "iostream"
Tile::Tile(int x, int y, const std::string& tileData)
	: x{ x }
	, y{ y }
	, tileData{ tileData }
{
}
void HighlightedTile::changeHighlightedTile(const SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_UP:
		y--;
		break;
	case SDLK_DOWN:
		y++;
		break;
	case SDLK_LEFT:
		x--;
		break;
	case SDLK_RIGHT:
		x++;
		break;
	default:
		break;
	}
	if (x < 0) x = 0;
	if (x > 25) x = 25;
	if (y < 0) y = 0;
	if (y > 25) y = 25;
	std::cout << x << " " << y << '\n';
}