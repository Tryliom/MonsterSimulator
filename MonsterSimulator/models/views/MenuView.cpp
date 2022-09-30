#include "MenuView.h"

#include "CreateMonsterView.h"
#include "../controllers/MainController.h"

void MenuView::Update(Console::Controller* controller, Console::Screen& screen)
{
	const MainController* mainController = dynamic_cast<MainController*>(controller);
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
	screen.Draw(Console::Button{ .Str = leftField, .X = screen.GetWidth() / 4, .Y = 5, .Selected = GetCurrentButton() == 0, .XCentered = true });
	screen.Draw(Console::Button{ .Str = rightField, .X = screen.GetWidth() * 3 / 4, .Y = 5, .Selected = GetCurrentButton() == 1, .XCentered = true });
	screen.Draw(Console::Button{ .Str = "Start fight", .X = screen.GetWidth() / 2, .Y = 10, .Selected = GetCurrentButton() == 2, .XCentered = true });

	screen.Draw(Console::Text{ .Str = _errorMessage, .X = screen.GetWidth() / 2, .Y = 12, .XCentered = true, .Background = Console::Background::RED });

	// Display controls for the user
	screen.Draw(Console::Text{ .Str = "Exit: Esc | Arrows: move | Confirm: Enter", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}

void MenuView::OnKeyPressed(Console::Controller* controller, const char key)
{
	_errorMessage.clear();

	if (key == Console::KEY_LEFT)
	{
		DecrementCurrentButton();
	}
	else if (key == Console::KEY_RIGHT)
	{
		IncrementCurrentButton();
	}
	else if (key == Console::KEY_DOWN)
	{
		SetCurrentButton(GetMaxButton() - 1);
	}
	else if (key == Console::KEY_UP)
	{
		SetCurrentButton(0);
	}
	else if (key == Console::KEY_ENTER)
	{
		const auto mainController = dynamic_cast<MainController*>(controller);

		if (GetCurrentButton() == 0)
		{
			mainController->ChangeView(new CreateMonsterView(mainController, true));
		}
		else if (GetCurrentButton() == 1)
		{
			mainController->ChangeView(new CreateMonsterView(mainController, false));
		}
		else if (GetCurrentButton() == 2)
		{
			if (mainController->CanStart())
			{
				//mainController->ChangeView(new FightView());
			}
			else
			{
				_errorMessage = "You need to create two monsters to start a fight";
			}
		}
	}

	View::OnKeyPressed(controller, key);
}
