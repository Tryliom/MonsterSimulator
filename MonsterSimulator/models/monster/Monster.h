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

	Race& GetRace() { return _race; }
	int GetHp() const { return _hp; }
	int GetAttack() const { return _attack; }
	int GetMaxHp() const { return _maxHp; }
	int GetArmor() const { return _armor; }
	int GetSpeed() const { return _speed; }
	float GetHpPercent() const { return static_cast<float>(_hp) / _maxHp; }
	void UpdateHp(const int hp) { _hp += hp; }
	void FullHeal() { _hp = _maxHp; }

	/**
	 * \brief Attack the given monster
	 * \param monster The monster to attack
	 * \return The amount of damage done
	 */
	int Attack(const Monster* monster) const;
	bool IsDead() const { return _hp <= 0; }

	explicit operator std::string() const;
};

