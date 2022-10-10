#pragma once
#include "Animation.h"
#include "../monster/Monster.h"
#include "../controllers/MainController.h"

/**
 * \brief The participant that is fighting another one in the fight view.
 */
class Participant
{
private:
	Monster* _monster{ nullptr };
	Animation _healthDifference{ Animation(0, 0) };
	Animation _attackAnimation{ Animation(0, 0) };
	bool _attacking{false};
	PositionX _x;
	PositionY _y;
	PositionX _xBar;
	PositionY _yBar;
	int _xCoefficient;

public:
	Participant() = default;
	Participant(Monster* monster, bool isLeft);

	Monster* GetMonster() const { return _monster; }
	Console::Image& GetSprite() const { return _monster->GetRace().GetSprite(); }

	void SetAttacking(const bool attacking) { _attacking = attacking; }
	bool IsAttacking() const { return _attacking; }
	void ToggleAttacking() { _attacking = !_attacking; }

	void SetHealthDifference(const float value, const int duration) { _healthDifference = Animation(value, duration); }
	Animation GetHealthDifference() const { return _healthDifference; }

	void SetAttackAnimation(const float value, const int duration) { _attackAnimation = Animation(value, duration); }
	Animation GetAttackAnimation() const { return _attackAnimation; }

	PositionX& GetX() { return _x; }
	PositionY& GetY() { return _y; }
	PositionX& GetXBar() { return _xBar; }
	PositionY& GetYBar() { return _yBar; }

	int GetXCoefficient() const { return _xCoefficient; }

	void UpdateAnimations();
	bool IsAnimationFinished() const;

	void PlayTurn(MainController* mainController, Participant* opponent);
	void ReceiveDamage(const int damage);

	int GetXOffset() const;
};

