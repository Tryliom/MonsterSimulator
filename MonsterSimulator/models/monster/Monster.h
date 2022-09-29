#pragma once
#include "Race.h"

class Monster
{
private:
	Race _race;
	int _hp;
	int _maxHp;
	int _armor;
	int _speed;

public:
	Monster(Race race, int hp, int armor, int speed);

	Race GetRace() const { return _race; }
	int GetHp() const { return _hp; }
	int GetMaxHp() const { return _maxHp; }
	int GetArmor() const { return _armor; }
	int GetSpeed() const { return _speed; }
};

