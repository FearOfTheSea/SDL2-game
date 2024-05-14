//render.cpp

#include "render.h"
#include <iostream>
#include "turncounter.h"
#include "SDL.h"
#include <string>
#include <SDL_ttf.h>

Render::Render(SDL_Renderer* renderer, const Map& map, Environment& environment, HighlightedTile& highlightedTile, TurnCounter& turnCounter, TTF_Font* font, InputHandler* inputHandler)
	: renderer(renderer)
	, environment(environment)
	, map(map)
    , highlightedTile(highlightedTile)
    , turnCounter(turnCounter)
    , font(font)
    , inputHandler(inputHandler)
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
void Render::renderUI(int turn)
{
    std::string turnText = "Current Turn: " + std::to_string(turnCounter.getTurn());
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, turnText.c_str(), {0, 0, 0});
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int texW, texH;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &texW, &texH);

    SDL_Rect dstrect = { 820, 700, texW, texH };

    SDL_RenderCopy(renderer, textTexture, nullptr, &dstrect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void Render::RenderScreen()
{
	clear();
	renderEnvironment();
    renderHighlightedTile();
    renderUI(turnCounter.getTurn());
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect outlineRect = { tileX, tileY , 32, 32 };
    SDL_RenderDrawRect(renderer, &outlineRect);
}