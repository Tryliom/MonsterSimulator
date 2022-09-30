#include "CreateMonsterView.h"

CreateMonsterView::CreateMonsterView(const bool left) : View(0, 6)
{
	_left = left;
}

void CreateMonsterView::Update(Console::Controller* controller, Console::Screen& screen)
{
	// Draw the title of the view
	screen.Draw(Console::Text{ .Str = "Monster Creator", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });

	// Draw each field in order to create a monster
	for (Race* race: RACES)
	{
		//TODO: Use _raceSelected, you don't need to select it just move it
	}
}

void CreateMonsterView::OnKeyPressed(Console::Controller* controller, const char key)
{
	if (key == Console::KEY_DOWN)
	{
		IncrementCurrentButton();
	}
	else if (key == Console::KEY_UP)
	{
		DecrementCurrentButton();
	}
	else if (key == Console::KEY_LEFT)
	{
		_raceSelected--;
	}
	else if (key == Console::KEY_RIGHT)
	{
		_raceSelected++;
	}
	else if (key == Console::KEY_ENTER)
	{
		//TODO: Check if every data is filled
		//TODO: Create the monster
	}

	if (_raceSelected >= static_cast<int>(RACES.size()) - 1)
	{
		_raceSelected = static_cast<int>(RACES.size()) - 1;
	}
	if (_raceSelected < 0)
	{
		_raceSelected = 0;
	}

	View::OnKeyPressed(controller, key);
}