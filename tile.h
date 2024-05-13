#pragma once

#include <string>
#include <vector>
#include <SDL.h>

class Tile
{
public:
	Tile() = default;
	Tile(int x, int y, const std::string& tileData);
	int getX() const { return x; }
	int getY() const { return y; }
	int getTileWidth() const { return tileWidth; }
	int getTileHeight() const { return tileHeight; }
	char getEnvironmentData() const { char c = tileData[0]; return c; }
private:
	int x{ -1 };
	int y{ -1 };
	std::string tileData{};
	int tileWidth{ 32 };
	int tileHeight{ 32 };
};

class HighlightedTile
{
public:
	HighlightedTile() : x{ 0 }, y{ 0 } {};
	void changeHighlightedTile(const SDL_Event& event);
	int getX() const { return x; }
	int getY() const { return y; }
private:
	int x;
	int y;	
};