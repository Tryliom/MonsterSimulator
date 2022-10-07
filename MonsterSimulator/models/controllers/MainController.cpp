#include "MainController.h"
#include "../views/MenuView.h"

MainController::MainController()
{
	Console::AudioManager::Play(MAIN_THEME_PATH);
	ChangeView(new MenuView(this));
}

int GetRandomNumber(const int min, const int max)
{
	srand(time(nullptr));
	return rand() % (max - min + 1) + min;
}

void MainController::ResetMonsters()
{
	_leftMonster = nullptr;
	_rightMonster = nullptr;
}

bool MainController::CanStart() const
{
	return IsAllMonsterCreated() && !HaveImpossibleStats();
}

bool MainController::IsAllMonsterCreated() const
{
	return _leftMonster != nullptr && _rightMonster != nullptr;
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
