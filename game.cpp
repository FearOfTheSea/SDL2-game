//game.cpp

#include "game.h"
#include "render.h"
#include "environment.h"
#include "inputhandler.h"
#include "tile.h"
#include <iostream>
#include <SDL_ttf.h>
Game::Game()
	: map("ASSETS/testMap.txt")
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("ASSETS/arial.ttf", 24);
	window = SDL_CreateWindow("Sovereign Domination", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	environment = Environment(renderer);
	highlightedTile = HighlightedTile();
	turnCounter = TurnCounter(0);
	inputHandler = InputHandler(&highlightedTile, &turnCounter);
	render = new Render(renderer, map, environment, highlightedTile, turnCounter, font, &inputHandler);
}
void Game::run()
{
	while (inputHandler.handleEvent())
	{
		render->RenderScreen();
	}
	close();
}
void Game::close()
{
	delete render;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_Quit();
}