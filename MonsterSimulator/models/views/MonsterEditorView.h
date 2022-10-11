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

class MonsterEditorView: public Console::View
{
private:
	Monster* _monster;

	std::string _errorMessage{};

	void createMonster(Console::Controller* controller);
public:
	explicit MonsterEditorView(MainController* mainController, Monster* monster);

	void OnKeyPressed(Console::Controller* controller, char key) override;
	void Update(Console::Controller* controller, Console::Screen& screen) override;
};

