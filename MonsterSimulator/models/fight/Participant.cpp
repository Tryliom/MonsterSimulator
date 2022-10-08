#include "Participant.h"

#include <numbers>

constexpr float X_BAR_OFFSET = -1.0f / 6.0f;

Participant::Participant(Monster* monster, bool isLeft)
{
	_monster = monster;
	_attacking = false;
	_x = isLeft ? PositionX(0.25f) : PositionX(0.75f);
	_y = PositionY(-monster->GetRace().GetSprite().GetHeight() / 2, 0.7f);
	_xBar = isLeft ? PositionX(0.25f + X_BAR_OFFSET) : PositionX(0.75f + X_BAR_OFFSET);
	_yBar = PositionY(2, 0.7f);
	_xCoefficient = isLeft ? 1 : -1;
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

void Participant::PlayTurn(const MainController* mainController, Participant* opponent)
{
	// Choose to attack
	_attackAnimation = Animation(
		10.0f,
		mainController->CurrentFPS
	);

	Utility::sleep(530);

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

int Participant::GetXOffset() const
{
	return sin(_attackAnimation.GetPercent() * std::numbers::pi) * _attackAnimation.GetValue() * _xCoefficient;
}
