#include "FightView.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

#include <thread>

FightView::FightView(MainController* mainController)
{
	_leftMonster = mainController->GetLeftMonster();
	_rightMonster = mainController->GetRightMonster();
	mainController->InitFight();
	startFightThread(mainController);
}

void FightView::startFightThread(const MainController* mainController)
{
	bool isLeftTurn = mainController->IsLeftStart();
	Monster* attacker = isLeftTurn ? _leftMonster : _rightMonster;
	Monster* defender = isLeftTurn ? _rightMonster : _leftMonster;

	std::thread thread([&]()
		{
			while (mainController->CanFightContinue())
			{
				attacker->Attack(defender);
				Utility::sleep(1000);
				Monster* temp = attacker;
				attacker = defender;
				defender = temp;
			}

			//ChangeView(new VictoryView(this));
		}
	);
	thread.detach();
}

void FightView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	screen.Draw(Console::Text{ .Str = static_cast<std::string>(*_leftMonster), .X = screen.GetWidth() / 4, .Y = 10});
	screen.Draw(Console::Text{ .Str = static_cast<std::string>(*_rightMonster), .X = screen.GetWidth() / 4 * 3, .Y = 10 });
}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}
