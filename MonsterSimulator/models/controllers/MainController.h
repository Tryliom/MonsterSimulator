#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../monster/Monster.h"

const std::string MAIN_THEME_PATH = "assets/audio/main_theme.wav";
const std::string BATTLE_MUSIC_PATH = "assets/audio/battle_theme.wav";
const std::string SPECIAL_BATTLE_MUSIC_PATH = "assets/audio/special_battle_theme.wav";

// The class that contains the main logic of the application and all the data used in it.
class MainController : public Console::Controller
{
private:
	// The monster at the left side of the screen
	Monster* _leftMonster;
	// The monster at the right side of the screen
	Monster* _rightMonster;
public:
	MainController();

	[[nodiscard]] Monster* GetLeftMonster() const { return _leftMonster; }
	[[nodiscard]] Monster* GetRightMonster() const { return _rightMonster; }

	/**
	 * \brief Delete the current monsters and create new ones empty
	 */
	void ResetMonsters();
	/**
	 * \brief Heal the monsters to full health
	 */
	void FullHeal() const;
	[[nodiscard]] bool IsLeftStart() const;

	/**
	 * \brief Check if the monsters are not of the same race, if they are created and if they have not impossible stats
	 * (both attack and armor are too low to make damage to each other)
	 * \return true if the fight can begin, false otherwise
	 */
	[[nodiscard]] bool CanFightBegin() const;
	/**
	 * \brief Check if the monsters are not dead
	 * \return true if the fight can continue, false otherwise
	 */
	[[nodiscard]] bool CanFightContinue() const;
	[[nodiscard]] bool HaveEachMonsterDifferentRaces() const;
	[[nodiscard]] bool IsAllMonsterCreated() const;
	/**
	 * \brief Check if the monsters have too low stats to make damage to each other
	 * \return true if the monsters have impossible stats, false otherwise
	 */
	[[nodiscard]] bool HaveImpossibleStats() const;
};

