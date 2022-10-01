#include "CreateMonsterView.h"
#include "../utilities/StringUtility.h"

CreateMonsterView::CreateMonsterView(const MainController* mainController, const bool left) : View(0, 6)
{
	_left = left;
	if (left)
	{
		_otherMonster = mainController->GetRightMonster();
	}
	else
	{
		_otherMonster = mainController->GetLeftMonster();
	}
}

void CreateMonsterView::Update(Console::Controller* controller, Console::Screen& screen)
{
	// Draw the title of the view
	screen.Draw(Console::Text{ .Str = "Monster Creator", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });

	// Draw each field in order to create a monster
	int xRace = screen.GetWidth() / 2;
	int i = 0;
	int y = 5;

	screen.Draw(Console::Text{ .Str = "Race:", .X = screen.GetWidth() / 4, .Y = y});

	for (const Race* race: RACES)
	{
		auto background = Console::Background::NONE;
		auto foreground = Console::Foreground::NONE;
		auto name = StringUtility::Capitalize(race->GetName());

		if (i == _raceSelected)
		{
			name.insert(0, "<");
			name += ">";
			if (GetCurrentButton() == 0)
			{
				background = Console::Background::CYAN;
				foreground = Console::Foreground::BLACK;
			}
			else
			{
				background = Console::Background::WHITE;
				foreground = Console::Foreground::BLACK;
			}
		}

		screen.Draw(Console::Text{ .Str = name, .X = xRace, .Y = y, .Background = background, .Foreground = foreground });
		i++;
		xRace += name.length() + 4;
	}

	y += 2;
	// Draw Hp field
	screen.Draw(Console::Text{ .Str = "Hp:", .X = screen.GetWidth() / 4, .Y = y });
	screen.Draw(Console::Field{ .Str = "<" + std::to_string(_hp) + ">", .X = screen.GetWidth() / 2, .Y = y, .Selected = GetCurrentButton() == 1, .ShowCursor = false});
	y += 2;
	// Draw Attack field
	screen.Draw(Console::Text{ .Str = "Attack:", .X = screen.GetWidth() / 4, .Y = y });
	screen.Draw(Console::Field{ .Str = "<" + std::to_string(_attack) + ">", .X = screen.GetWidth() / 2, .Y = y, .Selected = GetCurrentButton() == 2, .ShowCursor = false });
	y += 2;
	// Draw Armor field
	screen.Draw(Console::Text{ .Str = "Armor:", .X = screen.GetWidth() / 4, .Y = y });
	screen.Draw(Console::Field{ .Str = "<" + std::to_string(_armor) + ">", .X = screen.GetWidth() / 2, .Y = y, .Selected = GetCurrentButton() == 3, .ShowCursor = false });
	y += 2;
	// Draw Speed field
	screen.Draw(Console::Text{ .Str = "Speed:", .X = screen.GetWidth() / 4, .Y = y });
	screen.Draw(Console::Field{ .Str = "<" + std::to_string(_speed) + ">", .X = screen.GetWidth() / 2, .Y = y, .Selected = GetCurrentButton() == 4, .ShowCursor = false });
	y += 3;
	// Draw the confirm button
	screen.Draw(Console::Button{ .Str = "Confirm", .X = screen.GetWidth() / 2, .Y = y, .Selected = GetCurrentButton() == 5, .XCentered = true });
	// Draw the error message
	screen.Draw(Console::Text{ .Str = _errorMessage, .X = screen.GetWidth() / 2, .Y = y + 5, .XCentered = true, .Foreground = Console::Foreground::RED });

	// Display controls for the user
	screen.Draw(Console::Text{ .Str = "Exit: Esc | Left & right: select/change numbers | Up & down: move | Confirm: Enter", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}

void CreateMonsterView::OnKeyPressed(Console::Controller* controller, const char key)
{
	_errorMessage.clear();
	const int currentButton = GetCurrentButton();

	if (currentButton == 0)
	{
		if (key == Console::Key::Left)
		{
			_raceSelected--;
		}
		else if (key == Console::Key::Right)
		{
			_raceSelected++;
		}
	}
	else if (currentButton > 0 && currentButton < 5)
	{
		if (currentButton == 1)
		{
			if (key == Console::Key::Left)
			{
				if (_hp > 0)
				{
					_hp--;
				}
			}
			else if (key == Console::Key::Right)
			{
				_hp++;
			}
		}
		else if (currentButton == 2)
		{
			if (key == Console::Key::Left)
			{
				if (_attack > 0)
				{
					_attack--;
				}
			}
			else if (key == Console::Key::Right)
			{
				_attack++;
			}
		}
		else if (currentButton == 3)
		{
			if (key == Console::Key::Left)
			{
				if (_armor > 0)
				{
					_armor--;
				}
			}
			else if (key == Console::Key::Right)
			{
				_armor++;
			}
		}
		else if (currentButton == 4)
		{
			if (key == Console::Key::Left)
			{
				if (_speed > 0)
				{
					_speed--;
				}
			}
			else if (key == Console::Key::Right)
			{
				_speed++;
			}
		}
	}

	if (key == Console::Key::Down)
	{
		IncrementCurrentButton();
	}
	else if (key == Console::Key::Up)
	{
		DecrementCurrentButton();
	}
	else if (key == Console::Key::Enter && currentButton == 5)
	{
		if (_hp == 0 || _attack == 0 || _armor == 0 || _speed == 0)
		{
			_errorMessage = "All stats must be greater than 0";
		}
		else if (_otherMonster != nullptr && _otherMonster->GetRace().GetName() == _race->GetName())
		{
			_errorMessage = "The race of the monster can't be the same than the other";
		}
		else
		{
			const auto mainController = dynamic_cast<MainController*>(controller);
			const auto monster = new Monster(*_race, _hp, _attack, _armor, _speed);

			if (_left)
			{
				mainController->SetLeftMonster(monster);
			}
			else
			{
				mainController->SetRightMonster(monster);
			}

			mainController->GoBack();
		}
	}

	if (_raceSelected >= static_cast<int>(RACES.size()) - 1)
	{
		_raceSelected = static_cast<int>(RACES.size()) - 1;
	}
	if (_raceSelected < 0)
	{
		_raceSelected = 0;
	}

	_race = RACES[_raceSelected];

	View::OnKeyPressed(controller, key);
}