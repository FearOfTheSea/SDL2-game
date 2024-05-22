#pragma once

#include <array>
#include <vector>

class Unit
{
public:
	virtual ~Unit() = default;
	virtual int getUnitType() = 0;
	int getX() const { return x; }
	int getY() const { return y; }
	int getDefense() const { return defense; }
	int getAttack() const { return attack; }
	int getSupply() const { return supply; }

	void adjustDefense(int newDefense) { defense = newDefense; }
	void adjustAttack(int newAttack) { attack = newAttack; }
	void adjustSupply(int newSupply) { supply = newSupply; }

	void commandMove(int targetX, int targetY, const std::array<std::array<int, 25>, 25>& mapParameter, Unit* temp);
	void commandDefend();
	void commandResupply();

	void reactivate() { activated = false;  }
protected:
	int x{};
	int y{};
	int defense{ 100 };
	int attack{ 100 };
	int supply{ 100 };
	bool activated{ false };
};

class AllyUnit : public Unit
{
public:
	AllyUnit() = default;
	int getUnitType() override { return 1; }
	AllyUnit(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
};

class EnemyUnit : public Unit
{
public:
	EnemyUnit() = default;
	int getUnitType() override { return 2; }
	EnemyUnit(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
private:
	void decideCommand(std::vector<Unit*> allUnits);
	Unit* findNearestTarget(std::vector<Unit*> allUnits);
};