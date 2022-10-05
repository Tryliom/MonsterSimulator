#pragma once
#include "../controllers/MainController.h"

class MenuView : public Console::View
{
private:
	std::string _errorMessage;

public:
	explicit MenuView(MainController* mainController);

	void InitComponents(MainController* mainController);
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

