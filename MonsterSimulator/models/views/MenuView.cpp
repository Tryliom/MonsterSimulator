#include "MenuView.h"
#include "CreateMonsterView.h"
#include "FightView.h"
#include "../utilities/StringUtility.h"


MenuView::MenuView(MainController* mainController) : View()
{
	InitComponents(mainController);
}

void MenuView::InitComponents(MainController* mainController)
{
	const auto leftMonster = mainController->GetLeftMonster();
	const auto rightMonster = mainController->GetRightMonster();

	ClearComponents();

	if (leftMonster == nullptr)
	{
		AddComponent(new Console::BasicButton("Create monster", PositionX(0.25f), PositionY(5),
			[mainController](Console::Controller* controller) {controller->ChangeView(new CreateMonsterView(mainController, true)); }, true));
	}
	if (rightMonster == nullptr)
	{
		AddComponent(new Console::BasicButton("Create monster", PositionX(0.75f), PositionY(5),
			[mainController](Console::Controller* controller) {controller->ChangeView(new CreateMonsterView(mainController, false)); }, true));
	}

	AddComponent(new Console::BasicButton("Start fight", PositionX(0.5f), PositionY(10),
		[mainController, this](Console::Controller* controller)
		{
			if (mainController->CanStart())
			{
				controller->ClearStack();
				controller->SetView(new FightView(mainController));
			}
			else if (!mainController->IsAllMonsterCreated())
			{
				_errorMessage = "You need to create two monsters to start a fight";
			}
			else if (mainController->HaveImpossibleStats())
			{
				_errorMessage = "The two monsters can't harm each other with their stats";
			}
		}, true));
}

void MenuView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	const MainController* mainController = static_cast<MainController*>(controller);
	const auto leftMonster = mainController->GetLeftMonster();
	const auto rightMonster = mainController->GetRightMonster();

	if (leftMonster != nullptr)
	{
		screen.Draw(Console::Text{ .Str = StringUtility::Capitalize(leftMonster->GetRace().GetName()), .X = Console::Screen::WIDTH / 4, .Y = 5, .XCentered = true });
	}
	if (rightMonster != nullptr)
	{
		screen.Draw(Console::Text{ .Str = StringUtility::Capitalize(rightMonster->GetRace().GetName()), .X = Console::Screen::WIDTH * 3 / 4, .Y = 5, .XCentered = true });
	}

	// Draw the title of the view
	screen.Draw(Console::Text{ .Str = "Monster Simulator", .X = Console::Screen::WIDTH / 2, .Y = 2, .XCentered = true });

	screen.Draw(Console::Text{ .Str = _errorMessage, .X = Console::Screen::WIDTH / 2, .Y = 15, .XCentered = true, .Foreground = Console::Foreground::RED });

	// Display controls for the user
	screen.Draw(Console::Text{ .Str = "Exit: Esc | Arrows: move | Confirm: Enter | Reset: r", .X = Console::Screen::WIDTH / 2, .Y = Console::Screen::HEIGHT - 3, .XCentered = true });
}

void MenuView::OnKeyPressed(Console::Controller* controller, const char key)
{
	_errorMessage.clear();

	if (key == Console::Key::Left)
	{
		DecrementCurrentButton();
	}
	else if (key == Console::Key::Right)
	{
		IncrementCurrentButton();
	}
	else if (key == Console::Key::Down)
	{
		SetCurrentButton(GetMaxButton() - 1);
	}
	else if (key == Console::Key::Up)
	{
		SetCurrentButton(0);
	}

	if (key == 'r')
	{
		MainController* mainController = static_cast<MainController*>(controller);
		mainController->ResetMonsters();
		InitComponents(mainController);
	}

	View::OnKeyPressed(controller, key);
}
