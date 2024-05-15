//render.cpp

#include "render.h"
#include <iostream>
#include "turncounter.h"
#include "SDL.h"
#include <string>
#include <SDL_ttf.h>

Render::Render(SDL_Renderer* renderer, const Map& map, Environment& environment, HighlightedTile& highlightedTile, TurnCounter& turnCounter, TTF_Font* font, InputHandler* inputHandler
        ,Warrior* warrior)
	: renderer(renderer)
	, environment(environment)
	, map(map)
    , highlightedTile(highlightedTile)
    , turnCounter(turnCounter)
    , font(font)
    , inputHandler(inputHandler)
    , warrior(warrior)
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

    std::string turnText1 = "Arrows : navigate";

    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, turnText1.c_str(), { 0, 0, 0 });
    SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    SDL_QueryTexture(textTexture1, nullptr, nullptr, &texW, &texH);

    SDL_Rect dstrect1 = { 810, 500, texW, texH };

    SDL_RenderCopy(renderer, textTexture1, nullptr, &dstrect1);

    SDL_FreeSurface(textSurface1);
    SDL_DestroyTexture(textTexture1);

    std::string turnText2 = "Enter : new turn";

    SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, turnText2.c_str(), { 0, 0, 0 });
    SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    SDL_QueryTexture(textTexture2, nullptr, nullptr, &texW, &texH);

    SDL_Rect dstrect2 = { 810, 300, texW, texH };

    SDL_RenderCopy(renderer, textTexture2, nullptr, &dstrect2);

    SDL_FreeSurface(textSurface2);
    SDL_DestroyTexture(textTexture2);
}
void Render::renderWarrior()
{
    int x = warrior->getX();
    int y = warrior->getY();
    SDL_Surface* surface = SDL_LoadBMP("ASSETS/Swordman.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRectangle = { x * 32, y * 32, 32, 32 };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRectangle);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Render::RenderScreen()
{
	clear();
	renderEnvironment();
    renderHighlightedTile();
    renderUI(turnCounter.getTurn());
    
    renderStuctures(9, 10);
    renderWarrior();
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

void Render::renderStuctures(int x, int y)
{
        SDL_Surface* structureSurface = SDL_LoadBMP("ASSETS/Capital.bmp");
        SDL_Texture* structureTexture = SDL_CreateTextureFromSurface(renderer, structureSurface);
        if (structureTexture) {
            SDL_Rect dstRectangle = { x * 32, y * 32, 32, 32 };
            SDL_RenderCopy(renderer, structureTexture, nullptr, &dstRectangle);
        }
}