#include "MenuView.h"
#include "MonsterEditorView.h"
#include "FightView.h"
#include "../utilities/StringUtility.h"

MenuView::MenuView(MainController* mainController) : View()
{
	_mainController = mainController;
	
	setComponents({
		new Console::BasicButton(
			getFieldName(_mainController->GetLeftMonster()), PositionX(0.25f), PositionY(5),
			[this]()
			{
				_mainController->ChangeView(new MonsterEditorView(_mainController, _mainController->GetLeftMonster()));
			}, true
		),
		new Console::BasicButton(
			getFieldName(_mainController->GetRightMonster()), PositionX(0.75f), PositionY(5),
			[this]()
			{
				_mainController->ChangeView(new MonsterEditorView(_mainController, _mainController->GetRightMonster()));
			}, true
		),
		new Console::BasicButton("Start fight", PositionX(0.5f), PositionY(10),
		[this]()
			{
				if (_mainController->CanFightBegin())
				{
					_mainController->ClearStack();
					_mainController->SetView(new FightView(_mainController));
				}
				else if (!_mainController->HaveEachMonsterDifferentRaces())
				{
					_errorMessage = "You need to create two monsters to start a fight";
				}
				else if (!_mainController->IsAllMonsterCreated())
				{
					_errorMessage = "You need to create two monsters to start a fight";
				}
				else if (_mainController->HaveImpossibleStats())
				{
					_errorMessage = "The two monsters can't harm each other with their stats";
				}
			}, true
		)
	});
}

std::string MenuView::getFieldName(Monster* monster)
{
	if (monster->GetRace().GetRaceType() == RaceType::NONE)
	{
		return "Create monster";
	}

	return "Edit the " + StringUtility::Capitalize(monster->GetRace().GetName());
}

void MenuView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(Console::Controller::FPS), .X = 1, .Y = 1 });

	// Update current button according to the monsters
	getComponent<Console::BasicButton>(0)->SetText(getFieldName(_mainController->GetLeftMonster()));
	getComponent<Console::BasicButton>(1)->SetText(getFieldName(_mainController->GetRightMonster()));

	// Draw the title of the view
	screen.Draw(Console::Text{ 
		.Str = "Monster Simulator",
		.X = Console::Screen::WIDTH / 2, .Y = 2,
		.XCentered = true
	});

	// Draw the error message if there is one
	screen.Draw(Console::Text{ 
		.Str = _errorMessage,
		.X = Console::Screen::WIDTH / 2, .Y = 15,
		.XCentered = true, .Foreground = Console::Foreground::RED
	});

	// Display controls for the user
	screen.Draw(Console::Text{ 
		.Str = "Exit: Esc | Arrows: move | Confirm: Enter | Reset: r",
		.X = Console::Screen::WIDTH / 2, .Y = Console::Screen::HEIGHT - 3,
		.XCentered = true
	});
}

void MenuView::OnKeyPressed(const char key)
{
	_errorMessage.clear();

	if (key == Console::Key::Left)
	{
		decrementCurrentButton();
	}
	else if (key == Console::Key::Right)
	{
		incrementCurrentButton();
	}
	else if (key == Console::Key::Down)
	{
		setCurrentButton(getMaxButton() - 1);
	}
	else if (key == Console::Key::Up)
	{
		setCurrentButton(0);
	}

	if (key == 'r')
	{
		_mainController->ResetMonsters();
	}

	View::OnKeyPressed(key);
}
