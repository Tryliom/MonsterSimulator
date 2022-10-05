#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../monster/Monster.h"

class MainController : public Console::Controller
{
private:
	Monster* _leftMonster{ nullptr };
	Monster* _rightMonster{ nullptr };
public:
	MainController();

	Monster* GetLeftMonster() const { return _leftMonster; }
	Monster* GetRightMonster() const { return _rightMonster; }
	void SetLeftMonster(Monster* monster) { _leftMonster = monster; }
	void SetRightMonster(Monster* monster) { _rightMonster = monster; }

	void ResetMonsters();
	bool CanStart() const;
	bool HaveImpossibleStats() const;
	void InitFight() const;
	bool CanFightContinue() const;
	bool IsLeftStart() const;
};

