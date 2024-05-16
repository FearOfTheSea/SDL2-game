#pragma once

#include <SDL.h>

class Game
{
public:
	virtual ~Game() {}
	virtual void run();
protected:
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	virtual void render();
	virtual bool handleEvent(SDL_Event& event);
	virtual void nextGameState();
private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
};