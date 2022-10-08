#pragma once
#include "Race.h"

class Monster
{
private:
	Race _race;
	int _hp{ 150 };
	int _maxHp{ 150 };
	int _attack{ 20 };
	int _armor{ 5 };
	int _speed{ 10 };
public:
	Monster() = default;
	Monster(Race race, int hp, int attack, int armor, int speed);

	Race& GetRace() { return _race; }
	void SetRace(const Race& race) { _race = race; }

	int GetHp() const { return _hp; }
	int GetAttack() const { return _attack; }
	int GetMaxHp() const { return _maxHp; }
	int GetArmor() const { return _armor; }
	int GetSpeed() const { return _speed; }

	void SetHp(const int hp) { if (hp > 0) {_hp = hp; _maxHp = hp;} }
	void SetAttack(const int attack) { if (attack > 0) _attack = attack; }
	void SetArmor(const int armor) { if (armor > 0) _armor = armor; }
	void SetSpeed(const int speed) { if (speed > 0) _speed = speed; }

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

