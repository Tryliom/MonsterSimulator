#pragma once
#include "../../lib/ConsoleViewController.h"
#include "../monster/Monster.h"
#include "../controllers/MainController.h"

const std::vector<Race*> RACES = {
	new Dragon(),
	new Elf(),
	new Minotour(),
	new Phantom(),
	new Tribal()
};

class CreateMonsterView: public Console::View
{
private:
	bool _left;
	Monster* _otherMonster{ nullptr };
	Race* _race{RACES[0]};
	int _hp{0};
	int _attack{0};
	int _armor{0};
	int _speed{0};
	int _raceSelected{0};
	std::string _errorMessage{};

public:
	explicit CreateMonsterView(const MainController* mainController, bool left);

	void OnKeyPressed(Console::Controller* controller, char key) override;
	void Update(Console::Controller* controller, Console::Screen& screen) override;
};

