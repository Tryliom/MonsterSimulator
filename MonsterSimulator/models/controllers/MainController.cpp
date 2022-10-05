#include "MainController.h"
#include "../views/MenuView.h"

MainController::MainController()
{
	ChangeView(new MenuView(this));
}

int GetRandomNumber(int min, int max)
{
	srand(time(0));
	return rand() % (max - min + 1) + min;
}

void MainController::ResetMonsters()
{
	_leftMonster = nullptr;
	_rightMonster = nullptr;
}

bool MainController::CanStart() const
{
	return _leftMonster != nullptr && _rightMonster != nullptr && !HaveImpossibleStats();
}

bool MainController::HaveImpossibleStats() const
{
	return _leftMonster->GetAttack() - _rightMonster->GetArmor() <= 0 && _rightMonster->GetAttack() - _leftMonster->GetArmor() <= 0;
}

void MainController::InitFight() const
{
	_leftMonster->FullHeal();
	_rightMonster->FullHeal();
}

bool MainController::CanFightContinue() const
{
	return !_leftMonster->IsDead() && !_rightMonster->IsDead();
}

bool MainController::IsLeftStart() const
{
	if (_leftMonster->GetSpeed() > _rightMonster->GetSpeed())
	{
		return true;
	}

	if (_leftMonster->GetSpeed() < _rightMonster->GetSpeed())
	{
		return false;
	}
	
	return GetRandomNumber(0, 50) % 2 == 0;
}
