#include "Monster.h"

Monster::Monster(Race race, const int hp, const int attack, const int armor, const int speed) : _race(std::move(race))
{
	_hp = hp;
	_maxHp = hp;
	_attack = attack;
	_armor = armor;
	_speed = speed;
}

int Monster::Attack(const Monster* monster) const
{
	int damage = _attack - monster->GetArmor();

	if (damage < 0)
	{
		damage = 0;
	}

	if (damage > monster->GetHp())
	{
		damage = monster->GetHp();
	}

	return damage;
}

Monster::operator std::string() const
{
	return _race.GetName() + " (" + std::to_string(_hp) + "/" + std::to_string(_maxHp) + "hp)";
}


