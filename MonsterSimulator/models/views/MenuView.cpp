#include "MenuView.h"
#include "MonsterEditorView.h"
#include "FightView.h"
#include "../utilities/StringUtility.h"


MenuView::MenuView(MainController* mainController) : View()
{
	InitComponents(mainController);
}

std::string MenuView::getFieldName(Monster* monster)
{
	if (monster->GetRace().GetRaceType() == RaceType::NONE)
	{
		return "Create monster";
	}

	return "Edit the " + StringUtility::Capitalize(monster->GetRace().GetName());
}

void MenuView::InitComponents(MainController* mainController)
{
	ClearComponents();

	setComponents({
		new Console::BasicButton(
			getFieldName(mainController->GetLeftMonster()), PositionX(0.25f), PositionY(5),
			[mainController]()
			{
				mainController->ChangeView(new MonsterEditorView(mainController, mainController->GetLeftMonster()));
			}, true
		),
		new Console::BasicButton(
			getFieldName(mainController->GetRightMonster()), PositionX(0.75f), PositionY(5),
			[mainController]()
			{
				mainController->ChangeView(new MonsterEditorView(mainController, mainController->GetRightMonster()));
			}, true
		),
		new Console::BasicButton("Start fight", PositionX(0.5f), PositionY(10),
		[mainController, this]()
			{
				if (mainController->CanFightBegin())
				{
					mainController->ClearStack();
					mainController->SetView(new FightView(mainController));
				}
				else if (!mainController->HaveEachMonsterDifferentRaces())
				{
					_errorMessage = "You need to create two monsters to start a fight";
				}
				else if (!mainController->IsAllMonsterCreated())
				{
					_errorMessage = "You need to create two monsters to start a fight";
				}
				else if (mainController->HaveImpossibleStats())
				{
					_errorMessage = "The two monsters can't harm each other with their stats";
				}
			}, true
		)
	});
}

void MenuView::OnOpenView(Console::Controller* controller)
{
	InitComponents(static_cast<MainController*>(controller));
}

void MenuView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

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
		auto* mainController = static_cast<MainController*>(controller);
		mainController->ResetMonsters();
		InitComponents(mainController);
	}

	View::OnKeyPressed(controller, key);
}
