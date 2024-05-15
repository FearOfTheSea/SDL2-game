#pragma once

#include <SDL.h>

class Unit
{
protected:
	int x{ 9 };
	int y{ 10 };
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