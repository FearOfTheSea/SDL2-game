#pragma once

#include <SDL.h>

class Game
{
public:
	virtual ~Game() {}
	virtual void run();
	enum class difficulty{ easy, normal, hard };
	enum class state{ menu, play, victory, defeat };
protected:
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	virtual void render();
	virtual bool handleEvent(SDL_Event& event);
	void setDifficulty(difficulty newDifficulty);
	difficulty getDifficulty();
private:
	static difficulty gameDifficulty;
	static state gameState;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
};