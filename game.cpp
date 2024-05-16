#include "Game.h"
#include "GameMenu.h"
#include <iostream>

void Game::nextGameState() {}

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
void Game::run()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Sovereign Domination", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer) std::cout << "abc";
	GameMenu gameMenu;
}
bool Game::handleEvent(SDL_Event& event) { return true; }
void Game::render() {}
SDL_Renderer* Game::getRenderer()
{
	return renderer;
}
SDL_Window* Game::getWindow()
{
	return window;
}