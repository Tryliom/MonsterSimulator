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

public:
	Participant() = default;
	Participant(Monster* monster, const PositionX& x, const PositionY& y, const PositionX& xBar, const PositionY& yBar);

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

	void UpdateAnimations();
	bool IsAnimationFinished() const;

	void PlayTurn(const MainController* mainController, Participant* opponent) const;
	void ReceiveDamage(const int damage, const int fps);
};

