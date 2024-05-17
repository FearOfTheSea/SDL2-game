#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

class GameMenu : public Game
{
public:
	GameMenu();
	~GameMenu();
private:
	void run() override;
	void render() override;
	bool handleEvent(SDL_Event& event) override;
	SDL_Renderer* renderer{ getRenderer() };
	SDL_Window* window{ getWindow() };
};