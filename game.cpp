#include "Game.h"
#include "GameMenu.h"
#include "GamePlay.h"
#include <iostream>

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
void Game::run()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Sovereign Domination", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	GameMenu gameMenu;
	GamePlay GamePlay;
}
bool Game::handleEvent(SDL_Event& event) { return true; }
void Game::render() {}

Game::difficulty Game::gameDifficulty = Game::difficulty::easy;
Game::state Game::gameState = Game::state::menu;

void Game::setDifficulty(difficulty newDifficulty)
{
	gameDifficulty = newDifficulty;
}
SDL_Renderer* Game::getRenderer()
{
	return renderer;
}
SDL_Window* Game::getWindow()
{
	return window;
}

Game::difficulty Game::getDifficulty()
{
	return gameDifficulty;
}