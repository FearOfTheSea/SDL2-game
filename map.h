//map.h

#pragma once

#include "tile.h"
#include <string>
#include <vector>
#include <fstream>
class Map
{
public:
	Map(const std::string& mapData);
	const std::vector<std::vector<Tile>>& getTiles2DVector() const { return Tiles2DVector; }
private:
	int widthTiles{ 25 };
	int heightTiles{ 25 };
	std::vector<std::vector<Tile>> Tiles2DVector;
};