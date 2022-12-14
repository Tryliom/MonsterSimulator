#pragma once
#include "../controllers/MainController.h"

// Used to display the winner of the fight
class VictoryView : public Console::View
{
private:
	Monster* _winner;
	int _rounds;
public:
	VictoryView(MainController* mainController, int rounds);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

