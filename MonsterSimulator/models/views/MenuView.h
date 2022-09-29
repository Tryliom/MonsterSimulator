#pragma once
#include "../../lib/ConsoleViewController.h"

class MenuView : public Console::View
{
private:
	int _currentButton = 0;
	int _maxButtons = 3;
	std::string _errorMessage;

public:
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

