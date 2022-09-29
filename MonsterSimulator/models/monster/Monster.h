#pragma once
#include "Race.h"

class Monster
{
private:
	Race _race;
	int _hp;
	int _maxHp;
	int _attack;
	int _armor;
	int _speed;

public:
	Monster(Race race, int hp, int attack, int armor, int speed);

	Race GetRace() const { return _race; }
	int GetHp() const { return _hp; }
	int GetAttack() const { return _attack; }
	int GetMaxHp() const { return _maxHp; }
	int GetArmor() const { return _armor; }
	int GetSpeed() const { return _speed; }
	void UpdateHp(const int hp) { _hp += hp; }

	void Attack(Monster* monster) const;
	bool IsDead() const { return _hp <= 0; }
};
