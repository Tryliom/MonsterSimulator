#pragma once
#include "../controllers/MainController.h"

class VictoryView : public Console::View
{
private:
	Monster* _winner;
	int _rounds;
public:
	VictoryView(MainController* mainController, int rounds);

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

