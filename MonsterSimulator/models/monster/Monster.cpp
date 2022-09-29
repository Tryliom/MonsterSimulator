#include "Monster.h"

Monster::Monster(Race race, const int hp, const int attack, const int armor, const int speed) : _race(std::move(race))
{
	_hp = hp;
	_maxHp = hp;
	_attack = attack;
	_armor = armor;
	_speed = speed;
}

void Monster::Attack(Monster* monster) const
{
	int damage = monster->GetArmor() - _attack;

	if (damage > 0)
	{
		damage = 0;
	}

	monster->UpdateHp(damage);
}


