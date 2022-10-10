#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../monster/Monster.h"

const std::string MAIN_THEME_PATH = "assets/audio/main_theme.wav";
const std::string BATTLE_MUSIC_PATH = "assets/audio/battle_theme.wav";
const std::string SPECIAL_BATTLE_MUSIC_PATH = "assets/audio/special_battle_theme.wav";

class MainController : public Console::Controller
{
private:
	Monster* _leftMonster;
	Monster* _rightMonster;
public:
	MainController();

	Monster* GetLeftMonster() const { return _leftMonster; }
	Monster* GetRightMonster() const { return _rightMonster; }
	void SetLeftMonster(Monster* monster) { _leftMonster = monster; }
	void SetRightMonster(Monster* monster) { _rightMonster = monster; }

	void ResetMonsters();
	bool CanStart() const;
	bool HaveEachMonsterDifferentRaces() const;
	bool IsAllMonsterCreated() const;
	bool HaveImpossibleStats() const;
	void FullHeal() const;
	bool CanFightContinue() const;
	bool IsLeftStart() const;
};

