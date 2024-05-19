#include "Unit.h"
#include <cmath>
#include "GamePlay.h"
void Unit::commandMove(int targetX, int targetY, std::array<std::array<int, 25>, 25> mapDataParameter)
{
	if (activated == false)
	{
		return;
	}
	if (mapDataParameter[targetX][targetY] == static_cast<int>(GamePlay::terrain::water8))
		return;
	if (std::abs(targetX - x) <= 1 && std::abs(targetY - y))
	{
		if (supply < 30)
		{
			return;
		}
		switch (mapDataParameter[targetX][targetY])
		{
		case 0:
		case 1:
			supply -= 10;
			attack += 30;
			break;
		case 2:
		case 3:
			supply -= 30;
			attack += 40;
			break;
		case 4:
		case 5:
			supply -= 10;
			defense += 30;
		case 6:
		case 7:
			supply -= 30;
			defense += 40;
			break;
		}
		activated = true;
		x = targetY;
		y = targetY;
	}
}