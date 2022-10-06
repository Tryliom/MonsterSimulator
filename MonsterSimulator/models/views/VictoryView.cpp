#include "VictoryView.h"

#include "MenuView.h"

VictoryView::VictoryView(MainController* mainController, const int rounds)
{
	_winner = mainController->GetLeftMonster()->IsDead() ? mainController->GetRightMonster() : mainController->GetLeftMonster();
	_rounds = rounds;

	AddComponent(new Console::BasicButton("Back to menu", PositionX(0.5f), PositionY(0.5f), [](Console::Controller* controller)
		{
			MainController* mainController = static_cast<MainController*>(controller);
			mainController->ResetMonsters();
			mainController->ClearStack();
			mainController->SetView(new MenuView(mainController));
		}, true)
	);
}

void VictoryView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	screen.Draw(Console::Text{ .Str = "The fight has end in " + std::to_string(_rounds) + " rounds with " + static_cast<std::string>(*_winner) + " as winner !", 
		.X = Console::Screen::WIDTH / 2, .Y = 10, .XCentered = true });
}

void VictoryView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}
