#pragma once
#include "../controllers/MainController.h"

const std::vector<Race*> RACES = {
	new Dragon(),
	new Elf(),
	new Minotaur(),
	new Phantom(),
	new Tribal(),
	new Arceus()
};

// Used to create/edit a monster
class MonsterEditorView: public Console::View
{
private:
	Monster* _monster;
	MainController* _mainController;

	std::string _errorMessage{};

	void createMonster();
public:
	explicit MonsterEditorView(MainController* mainController, Monster* monster);

	void OnKeyPressed(char key) override;
	void Update(Console::Screen& screen) override;
};

