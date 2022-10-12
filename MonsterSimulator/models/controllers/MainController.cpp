#include "MainController.h"
#include "../views/MenuView.h"

MainController::MainController()
{
	_leftMonster = new Monster();
	_rightMonster = new Monster();

	Console::AudioManager::Play(MAIN_THEME_PATH, true);

	ChangeView(new MenuView(this));
}

int GetRandomNumber(const int min, const int max)
{
	srand(static_cast<unsigned>(time(nullptr)));
	return rand() % (max - min + 1) + min;
}

void MainController::ResetMonsters()
{
	_leftMonster = new Monster();
	_rightMonster = new Monster();
}

bool MainController::CanFightBegin() const
{
	return HaveEachMonsterDifferentRaces() && IsAllMonsterCreated() && !HaveImpossibleStats();
}

bool MainController::CanFightContinue() const
{
	return !_leftMonster->IsDead() && !_rightMonster->IsDead();
}

bool MainController::HaveEachMonsterDifferentRaces() const
{
	return _leftMonster->GetRace().GetName() != _rightMonster->GetRace().GetName();
}

bool MainController::IsAllMonsterCreated() const
{
	return _leftMonster->GetRace().GetRaceType() != RaceType::NONE && _rightMonster->GetRace().GetRaceType() != RaceType::NONE;
}

bool MainController::HaveImpossibleStats() const
{
	return _leftMonster->GetAttack() - _rightMonster->GetArmor() <= 0 && _rightMonster->GetAttack() - _leftMonster->GetArmor() <= 0;
}

void MainController::FullHeal() const
{
	_leftMonster->FullHeal();
	_rightMonster->FullHeal();
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
