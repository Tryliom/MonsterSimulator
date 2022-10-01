#pragma once
#include "../../lib/ConsoleViewController.h"
#include "../controllers/MainController.h"

class MenuView : public Console::View
{
private:
	std::string _errorMessage;

public:
	explicit MenuView(const MainController* mainController);
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

