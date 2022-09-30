#pragma once
#include "../../lib/ConsoleViewController.h"
#include "../monster/Monster.h"

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
	Race* _race{nullptr};
	int _hp{0};
	int _attack{0};
	int _armor{0};
	int _speed{0};
	int _raceSelected{0};

public:
	explicit CreateMonsterView(bool left);

	void OnKeyPressed(Console::Controller* controller, char key) override;
	void Update(Console::Controller* controller, Console::Screen& screen) override;
};

