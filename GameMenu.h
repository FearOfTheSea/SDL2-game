#pragma once

#include <SDL.h>
#include "Game.h"

class GameMenu : public Game
{
public:
	GameMenu();
	~GameMenu() = default;
	void run() override;
protected:
	void render() override;
	bool handleEvent(SDL_Event& event) override;
	void nextGameState() override;
private:
	SDL_Renderer* renderer{ getRenderer() };
	SDL_Window* window{ getWindow() };
};

