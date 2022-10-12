#pragma once
#include "../controllers/MainController.h"

// Used to display the main menu with the two monsters creator and the fight button
class MenuView : public Console::View
{
private:
	std::string _errorMessage;
	MainController* _mainController;

	static std::string getFieldName(Monster* monster);
public:
	explicit MenuView(MainController* mainController);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

