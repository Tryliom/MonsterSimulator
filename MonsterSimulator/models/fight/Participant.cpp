#include "Participant.h"

Participant::Participant(Monster* monster, const PositionX& x, const PositionY& y, const PositionX& xBar, const PositionY& yBar)
{
	_monster = monster;
	_attacking = false;
	_x = x;
	_y = y;
	_xBar = xBar;
	_yBar = yBar;
}

void Participant::UpdateAnimations()
{
	_healthDifference.Update();
	_attackAnimation.Update();
}

bool Participant::IsAnimationFinished() const
{
	return _healthDifference.IsFinished() && _attackAnimation.IsFinished();
}

void Participant::PlayTurn(const MainController* mainController, Participant* opponent) const
{
	// Choose to attack
	const int damageDealt = _monster->Attack(opponent->GetMonster());

	opponent->ReceiveDamage(damageDealt, mainController->CurrentFPS);
}

void Participant::ReceiveDamage(const int damage, const int fps)
{
	_monster->UpdateHp(- damage);

	if (damage > 0)
	{
		_healthDifference = Animation(
			static_cast<float>(damage) / static_cast<float>(_monster->GetMaxHp()),
			fps
		);
	}
}
