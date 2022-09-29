#include "Monster.h"

Monster::Monster(Race race, const int hp, const int armor, const int speed) : _race(std::move(race))
{
	_hp = hp;
	_maxHp = hp;
	_armor = armor;
	_speed = speed;
}


