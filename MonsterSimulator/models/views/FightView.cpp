#include "FightView.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "VictoryView.h"

#include <thread>

FightView::FightView(MainController* mainController)
{
	_leftParticipant = new Participant(mainController->GetLeftMonster());
	_rightParticipant = new Participant(mainController->GetRightMonster());
	_rounds = 0;

	//TODO: Reverse doesn't work
	_rightParticipant->Monster->GetRace().GetSprite().Reverse();
	
	Console::AudioManager::Play(BATTLE_MUSIC_PATH);

	mainController->InitFight();
	startFightThread(mainController);
}

void FightView::startFightThread(MainController* mainController)
{
	const bool isLeftTurn = mainController->IsLeftStart();
	Participant* attacker = isLeftTurn ? _leftParticipant : _rightParticipant;
	Participant* defender = isLeftTurn ? _rightParticipant : _leftParticipant;

	std::thread thread([&]()
		{
			while (mainController->CanFightContinue())
			{
				_rounds++;
				const int previousHp = defender->Monster->GetHp();
				attacker->Monster->Attack(defender->Monster);
				int diff = previousHp - defender->Monster->GetHp();
				defender->HpDiff = Animation(diff, 30);
				while (!defender->HpDiff.IsFinished())
				{
					Utility::sleep(1000);
				}
				Participant* temp = attacker;
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

void FightView::drawMonster(Console::Screen& screen, Participant* participant)
{
	const bool isLeftMonster = participant->Monster == _leftParticipant->Monster;

	// Define constants
	const int spriteHeight = participant->Monster->GetRace().GetSprite().GetHeight();
	const int x = isLeftMonster ? (Console::Screen::WIDTH / 4) : (Console::Screen::WIDTH * 3 / 4);
	const int y = PositionY(- spriteHeight / 2, 0.7f).GetValue();

	screen.Draw(participant->Monster->GetRace().GetSprite(), x, y, true, true);
	drawHpBar(screen, participant, x, y + spriteHeight / 2 + 2);
}

void FightView::drawHpBar(Console::Screen& screen, Participant* participant, const int x, const int y)
{
	// Define constants
	const int barWidth = Console::Screen::WIDTH_PIXEL / 3;
	constexpr int barHeight = 15;
	constexpr int barBorderWidth = 4;
	const int currentBarWidth = static_cast<int>(static_cast<float>(barWidth) * participant->Monster->GetHpPercent());
	const int currentHpDiffWidth = static_cast<int>(static_cast<float>(barWidth) * static_cast<float>(participant->HpDiff.Value) / 100.0f);
	const int yBar = y * Console::Screen::PIXEL_RATIO_Y;
	const int xBar = x * Console::Screen::PIXEL_RATIO_X - barWidth / 2;

	// Draw the border of the bar
	screen.DrawRect(xBar - barBorderWidth, yBar - barBorderWidth, barWidth + barBorderWidth * 2, barHeight + barBorderWidth * 2, BAR_BORDER_COLOR);
	// Draw the background of the bar
	screen.DrawRect(xBar, yBar, barWidth, barHeight, BAR_BACK_COLOR);
	// Draw the content of the bar with a gradient of the main color
	screen.DrawRect(xBar, yBar, currentBarWidth, barHeight, BAR_CONTENT_COLOR3);
	screen.DrawRect(xBar, yBar, currentBarWidth, barHeight * 2 / 3, BAR_CONTENT_COLOR2);
	screen.DrawRect(xBar, yBar, currentBarWidth, barHeight * 1 / 3, BAR_CONTENT_COLOR1);

	if (!participant->HpDiff.IsFinished())
	{
		const int width = static_cast<int>(static_cast<float>(currentHpDiffWidth) * 1.0f - participant->HpDiff.GetPercent());
		// Draw the difference of the hp bar with a gradient of the diff color
		screen.DrawRect(xBar + currentBarWidth, yBar, width, barHeight, BAR_CONTENT_DIFF_COLOR3);
		screen.DrawRect(xBar + currentBarWidth, yBar, width, barHeight * 2 / 3, BAR_CONTENT_DIFF_COLOR2);
		screen.DrawRect(xBar + currentBarWidth, yBar, width, barHeight * 1 / 3, BAR_CONTENT_DIFF_COLOR1);
	}
}

void FightView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(controller->CurrentFPS), .X = 1, .Y = 1 });

	screen.Draw(Console::Text{ .Str = "Round " + std::to_string(_rounds), .X = Console::Screen::WIDTH / 2, .Y = 2, .XCentered = true });

	drawMonster(screen, _leftParticipant);
	drawMonster(screen, _rightParticipant);

	if (!_leftParticipant->HpDiff.IsFinished())
	{
		_leftParticipant->HpDiff.Update();
	}
	if (!_rightParticipant->HpDiff.IsFinished())
	{
		_rightParticipant->HpDiff.Update();
	}
}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}
