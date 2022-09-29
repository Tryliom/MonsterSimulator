#include "CreateMonsterView.h"

CreateMonsterView::CreateMonsterView(const bool left)
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
		
	}
}

void CreateMonsterView::OnKeyPressed(Console::Controller* controller, char key)
{

}