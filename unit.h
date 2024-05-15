#pragma once

#include <SDL.h>

class Unit
{
protected:
	int x{ 3 };
	int y{ 3 };
public:
	Unit() = default;
	int getX() { return x; }
	int getY() { return y; }
	void moveUnit(SDL_Event event);
};

class Warrior : public Unit
{
private:
	int movement{ 1 };
};

