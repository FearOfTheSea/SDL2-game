//render.cpp

#include "render.h"
#include <iostream>

Render::Render(SDL_Renderer* renderer, const Map& map, Environment& environment, HighlightedTile& highlightedTile)
	: renderer(renderer)
	, environment(environment)
	, map(map)
    , highlightedTile(highlightedTile)
{
    environment.importAssets();
}
Render::~Render()
{
}
void Render::clear()
{
	SDL_RenderClear(renderer);
}
void Render::present()
{
	SDL_RenderPresent(renderer);
}
void Render::RenderScreen()
{
	clear();
	renderEnvironment();
    renderHighlightedTile();
	present();
}
void Render::renderEnvironment()
{
    const auto& tiles2DVector = map.getTiles2DVector();
    for (int y = 0; y < tiles2DVector.size(); ++y) {
        for (int x = 0; x < tiles2DVector[y].size(); ++x) {
            const Tile& tile = tiles2DVector[y][x];
            const char& environmentCode = tile.getEnvironmentData();
            SDL_Texture* texture = environment.getTextureFromID(environmentCode);

            if (texture) {
                SDL_Rect dstRectangle = { x * 32, y * 32, 32, 32 };
                SDL_RenderCopy(renderer, texture, nullptr, &dstRectangle);
            }
        }
    }
}
void Render::renderHighlightedTile()
{
    int tileX = highlightedTile.getX() * 32;
    int tileY = highlightedTile.getY() * 32;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect outlineRect = { tileX - 2, tileY - 2, 36, 36 };
    SDL_RenderDrawRect(renderer, &outlineRect);
}