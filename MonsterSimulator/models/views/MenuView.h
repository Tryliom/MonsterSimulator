#pragma once
#include "../../lib/ConsoleViewController.h"

class MenuView : public Console::View
{
private:
	std::string _errorMessage;

public:
	MenuView() : View(0, 3) {}
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

