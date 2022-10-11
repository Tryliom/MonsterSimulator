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
	int _xCoefficient{1};

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

	/**
	 * \brief Call the update method of the animations of the participant
	 * \param deltaTime The time elapsed since the last update in nanoseconds
	 */
	void UpdateAnimations(int deltaTime);
	/**
	 * \brief Check if the animations of the participant are finished
	 * \return True if the animations are finished, false otherwise
	 */
	bool IsAnimationFinished() const;

	/**
	 * \brief Called when the participant is playing its turn and need to choose an action
	 * \param mainController The main controller of the application
	 * \param opponent The opponent of the participant
	 */
	void PlayTurn(MainController* mainController, Participant* opponent);
	/**
	 * \brief Called when the participant is receiving damage
	 * \param damage The amount of damage received
	 */
	void ReceiveDamage(const int damage);

	/**
	 * \brief Get the x offset that the participant have while being his attack animation.
	 * Sin function is used to make the participant move back and forth.
	 * \return The x offset
	 */
	int CalculateAttackXOffset() const;
};

