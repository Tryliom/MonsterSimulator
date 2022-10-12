#include "VictoryView.h"

#include "MenuView.h"

VictoryView::VictoryView(MainController* mainController, const int rounds)
{
	_winner = mainController->GetLeftMonster()->IsDead() ? mainController->GetRightMonster() : mainController->GetLeftMonster();
	_rounds = rounds;

	addComponent(new Console::BasicButton("Back to menu", PositionX(0.5f), PositionY(0.5f), [mainController]()
		{
			mainController->FullHeal();
			mainController->ClearStack();
			mainController->SetView(new MenuView(mainController));
		}, true)
	);
}

void VictoryView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{ .Str = "The fight has end in " + std::to_string(_rounds) + " rounds with " + static_cast<std::string>(*_winner) + " as winner !", 
		.X = Console::Screen::WIDTH / 2, .Y = 10, .XCentered = true });
}

void VictoryView::OnKeyPressed(const char key)
{
	View::OnKeyPressed(key);
}
