#pragma once
#include "../controllers/MainController.h"

class FightView : public Console::View
{
private:

public:
	explicit FightView(MainController* mainController);

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

