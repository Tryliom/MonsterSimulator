#include "FightView.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "VictoryView.h"

#include <thread>

FightView::FightView(MainController* mainController)
{
	_leftMonster = mainController->GetLeftMonster();
	_rightMonster = mainController->GetRightMonster();
	_rounds = 0;

	//TODO: Reverse doesn't work
	_rightMonster->GetRace().GetSprite().Reverse();
	
	Console::AudioManager::Play(BATTLE_MUSIC_PATH);

	mainController->InitFight();
	startFightThread(mainController);
}

void FightView::startFightThread(MainController* mainController)
{
	const bool isLeftTurn = mainController->IsLeftStart();
	Monster* attacker = isLeftTurn ? _leftMonster : _rightMonster;
	Monster* defender = isLeftTurn ? _rightMonster : _leftMonster;

	std::thread thread([&]()
		{
			while (mainController->CanFightContinue())
			{
				_rounds++;
				attacker->Attack(defender);
				Utility::sleep(1000);
				Monster* temp = attacker;
				attacker = defender;
				defender = temp;
			}

			Console::AudioManager::Stop();
			mainController->ClearStack();
			mainController->SetView(new VictoryView(mainController, _rounds));
		}
	);
	thread.detach();
}

void FightView::drawMonster(Console::Screen& screen, const Monster* monster) const
{
	const bool isLeftMonster = monster->GetRace().GetName() == _leftMonster->GetRace().GetName();
	
	const int spriteHeight = monster->GetRace().GetSprite().GetHeight();
	const int x = isLeftMonster ? (Console::Screen::WIDTH / 4) : (Console::Screen::WIDTH * 3 / 4);
	const int y = PositionY(- spriteHeight / 2, 0.7f).GetValue();

	screen.Draw(monster->GetRace().GetSprite(), x, y, true, true);
	drawHpBar(screen, monster, x, y + spriteHeight / 2 + 2);
}

void FightView::drawHpBar(Console::Screen& screen, const Monster* monster, const int x, const int y)
{
	const int barWidth = Console::Screen::WIDTH_PIXEL / 3;
	constexpr int barHeight = 20;
	constexpr int barBorderWidth = 4;
	const int currentBarWidth = static_cast<int>(static_cast<float>(barWidth) * monster->GetHpPercent());
	const int yBar = y * Console::Screen::PIXEL_RATIO_Y;
	const int xBar = x * Console::Screen::PIXEL_RATIO_X - barWidth / 2;

	screen.DrawRect(xBar - barBorderWidth, yBar - barBorderWidth, barWidth + barBorderWidth * 2, barHeight + barBorderWidth * 2, BAR_BORDER_COLOR);
	screen.DrawRect(xBar, yBar, barWidth, barHeight, BAR_BACK_COLOR);
	screen.DrawRect(xBar, yBar, currentBarWidth, barHeight, BAR_CONTENT_COLOR);
}

void FightView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	screen.Draw(Console::Text{ .Str = "Round " + std::to_string(_rounds), .X = Console::Screen::WIDTH / 2, .Y = 2, .XCentered = true });

	drawMonster(screen, _leftMonster);
	drawMonster(screen, _rightMonster);
}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}
