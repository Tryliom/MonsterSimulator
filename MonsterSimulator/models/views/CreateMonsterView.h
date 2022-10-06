#pragma once
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
	int _hp{100};
	int _attack{10};
	int _armor{1};
	int _speed{1};
	int _raceSelected{0};
	std::string _errorMessage{};

	void createMonster(Console::Controller* controller);
public:
	explicit CreateMonsterView(const MainController* mainController, bool left);

	void OnKeyPressed(Console::Controller* controller, char key) override;
	void Update(Console::Controller* controller, Console::Screen& screen) override;
};

