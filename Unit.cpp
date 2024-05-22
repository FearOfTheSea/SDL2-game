#include "Unit.h"
#include <cmath>
#include "GamePlay.h"
#include <unordered_map>
#include <iostream>
#include <queue>
#include <functional>
using namespace std;

void Unit::commandMove(int targetX, int targetY, const std::array<std::array<int, 25>, 25>& mapDataParameter, Unit* temp)
{
	if (activated == true)
	{
		return;
	}
	if (mapDataParameter[targetX][targetY] == static_cast<int>(GamePlay::terrain::water8))
		return;
	if (temp == nullptr) 
	{
		if ((std::abs(targetX - x) <= 1) && (std::abs(targetY - y) <= 1))
		{
			if (supply < 30)
			{
				std::cout << "Not enough supply!";
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
				break;
			case 6:
			case 7:
				supply -= 30;
				defense += 40;
				break;
			}

			activated = true;
			x = targetX;
			y = targetY;
			
			return;
		}
	}
	else if (temp->getUnitType() == 1)
		return;
	else if (temp->getUnitType() == 2)
	{
		temp->adjustSupply(temp->getSupply() + temp->getDefense() - attack - defense);
		adjustSupply(supply + attack + defense - temp->getAttack() - temp->getDefense());
		adjustDefense(2 * temp->getDefense() - attack);
		activated = true;
		return;
	}
}
void Unit::commandResupply()
{
	if (activated == true)
		return;
	activated = true;
	supply += 100;
}

void Unit::commandDefend()
{
	if (activated == true)
		return;
	activated = true;
	defense += 100;
}

void EnemyUnit::decideCommand(std::vector<Unit*> allUnit)
{
	if (supply < 50)
	{
		commandResupply();
		return;
	}
	if (defense < 50)
	{
		commandDefend();
		return;
	}
	Unit* currentTarget = findNearestTarget(allUnit);

}

Unit* EnemyUnit::findNearestTarget(std::vector<Unit*> allUnits)
{
	Unit* nearestTarget = nullptr;
	double minDistance = std::numeric_limits<double>::max();

	for (Unit* unit : allUnits)
	{
		if (unit->getUnitType() == 1) // Check if the unit is an AllyUnit
		{
			int dx = unit->getX() - this->x;
			int dy = unit->getY() - this->y;
			double distance = std::sqrt(dx * dx + dy * dy);

			if (distance < minDistance)
			{
				minDistance = distance;
				nearestTarget = unit;
			}
		}
	}

	return nearestTarget;
}

