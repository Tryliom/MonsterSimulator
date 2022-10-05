#pragma once
#include "../controllers/MainController.h"

class FightView : public Console::View
{
private:
	Monster* _leftMonster;
	Monster* _rightMonster;

	void startFightThread(const MainController* mainController);
public:
	explicit FightView(MainController* mainController);
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

