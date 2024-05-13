//map.cpp

#include "map.h"
#include <iostream>

Map::Map(const std::string& mapData)
{ 
	Tiles2DVector.resize(heightTiles, std::vector<Tile>(widthTiles));

	std::ifstream file(mapData);

	for (int y{ 0 }; y < heightTiles; ++y)
	{
		for (int x{ 0 }; x < widthTiles; ++x)
		{
			std::string extractedTileData{};
			file >> extractedTileData;
			Tiles2DVector[x][y] = Tile{ x, y, extractedTileData };
		}
	}

	file.close();
}