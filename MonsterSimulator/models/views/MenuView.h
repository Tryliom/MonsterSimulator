#pragma once
#include "../controllers/MainController.h"

// Used to display the main menu with the two monsters creator and the fight button
class MenuView : public Console::View
{
private:
	std::string _errorMessage;

	static std::string getFieldName(Monster* monster);
public:
	explicit MenuView(MainController* mainController);

	void InitComponents(MainController* mainController);

	void OnOpenView(Console::Controller* controller) override;
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

