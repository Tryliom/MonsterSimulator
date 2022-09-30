#include "MenuView.h"
#include "../controllers/MainController.h"

void MenuView::Update(Console::Controller* controller, Console::Screen& screen)
{
	MainController* mainController = dynamic_cast<MainController*>(controller);
	const auto leftMonster = mainController->GetLeftMonster();
	const auto rightMonster = mainController->GetRightMonster();
	std::string leftField = "Create a monster";
	std::string rightField = "Create a monster";

	if (leftMonster != nullptr)
	{
		leftField = leftMonster->GetRace().GetName();
	}
	if (rightMonster != nullptr)
	{
		rightField = rightMonster->GetRace().GetName();
	}

	// Draw the title of the view
	screen.Draw(Console::Text{ .Str = "Monster Simulator", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });
	// Draw the menu buttons
	screen.Draw(Console::Temp{ .Str = leftField, .X = screen.GetWidth() / 4, .Y = 5, .Selected = _currentButton == 0, .XCentered = true });
	screen.Draw(Console::Temp{ .Str = rightField, .X = screen.GetWidth() * 3 / 4, .Y = 5, .Selected = _currentButton == 1, .XCentered = true });
	screen.Draw(Console::Temp{ .Str = "Start fight", .X = screen.GetWidth() / 2, .Y = 10, .Selected = _currentButton == 2, .XCentered = true });

	screen.Draw(Console::Text{ .Str = _errorMessage, .X = screen.GetWidth() / 2, .Y = 12, .XCentered = true, .Background = Console::Background::RED });

	// Display controls for the user
	screen.Draw(Console::Text{ .Str = "Exit: Esc | Arrows: move | Confirm: Enter", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}

void MenuView::OnKeyPressed(Console::Controller* controller, const char key)
{
	_errorMessage.clear();

	if (key == Console::KEY_LEFT)
	{
		_currentButton--;
	}
	else if (key == Console::KEY_RIGHT)
	{
		_currentButton++;
	}
	else if (key == Console::KEY_DOWN)
	{
		_currentButton = _maxButtons - 1;
	}
	else if (key == Console::KEY_UP)
	{
		_currentButton = 0;
	}
	else if (key == Console::KEY_ENTER)
	{
		if (_currentButton == 0)
		{
			//dynamic_cast<MainController*>(controller)->ChangeView(new CreateMonsterView(true));
		}
		else if (_currentButton == 1)
		{
			//dynamic_cast<MainController*>(controller)->ChangeView(new CreateMonsterView(false));
		}
		else if (_currentButton == 2)
		{
			if (const auto mainController = dynamic_cast<MainController*>(controller); mainController->CanStart())
			{
				//mainController->ChangeView(new FightView());
			}
			else
			{
				_errorMessage = "You need to create two monsters to start a fight";
			}
		}
	}

	if (_currentButton >= _maxButtons)
	{
		_currentButton = _maxButtons - 1;
	}
	if (_currentButton < 0)
	{
		_currentButton = 0;
	}
}
