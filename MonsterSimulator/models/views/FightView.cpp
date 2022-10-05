#include "FightView.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "VictoryView.h"

#include <thread>

constexpr COLORREF BAR_COLOR = RGB(200, 50, 50);

FightView::FightView(MainController* mainController)
{
	_leftMonster = mainController->GetLeftMonster();
	_rightMonster = mainController->GetRightMonster();
	_yLeftMonster = PositionY(- _leftMonster->GetRace().GetSprite().GetHeight() / 2, 0.5f);
	_yRightMonster = PositionY(- _rightMonster->GetRace().GetSprite().GetHeight() / 2, 0.5f);

	mainController->InitFight();
	startFightThread(mainController);
}

void FightView::startFightThread(MainController* mainController) const
{
	const bool isLeftTurn = mainController->IsLeftStart();
	Monster* attacker = isLeftTurn ? _leftMonster : _rightMonster;
	Monster* defender = isLeftTurn ? _rightMonster : _leftMonster;

	std::thread thread([&]()
		{
			int rounds = 0;
			while (mainController->CanFightContinue())
			{
				rounds++;
				attacker->Attack(defender);
				Utility::sleep(1000);
				Monster* temp = attacker;
				attacker = defender;
				defender = temp;
			}

			mainController->ClearStack();
			mainController->SetView(new VictoryView(mainController, rounds));
		}
	);
	thread.detach();
}

void FightView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	const float ratioPixel = static_cast<float>(Console::Screen::WIDTH_PIXEL) / Console::Screen::WIDTH;
	const int xLeft = screen.GetWidth() / 4;
	const int xRight = screen.GetWidth() * 3 / 4;
	const int leftWidth = _leftMonster->GetRace().GetSprite().GetWidth();
	const int rightWidth = _rightMonster->GetRace().GetSprite().GetWidth();
	const int leftBarWidth = static_cast<int>(static_cast<float>(leftWidth) * _leftMonster->GetHpPercent() * ratioPixel);
	const int rightBarWidth = static_cast<int>(static_cast<float>(rightWidth) * _rightMonster->GetHpPercent() * ratioPixel);

	screen.Draw(_leftMonster->GetRace().GetSprite(), xLeft, _yLeftMonster.GetValue(), true, true);
	screen.Draw(_rightMonster->GetRace().GetSprite(), xRight, _yRightMonster.GetValue(), true, true);

	screen.DrawRect(xLeft * ratioPixel - leftWidth / 2, Console::Screen::HEIGHT_PIXEL / 2 + 50, leftBarWidth, 20, BAR_COLOR);
	screen.DrawRect(xRight * ratioPixel - rightWidth / 2 * ratioPixel, Console::Screen::HEIGHT_PIXEL / 2 + 50, rightBarWidth, 20, BAR_COLOR);

	/*screen.Draw(Console::Text{ .Str = static_cast<std::string>(*_leftMonster), .X = screen.GetWidth() / 4, .Y = 10, .XCentered = true });
	screen.Draw(Console::Text{ .Str = static_cast<std::string>(*_rightMonster), .X = screen.GetWidth() / 4 * 3, .Y = 10, .XCentered = true });*/
}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}
