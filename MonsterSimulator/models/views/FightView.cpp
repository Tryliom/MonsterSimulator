#include "FightView.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "VictoryView.h"

#include <thread>

FightView::FightView(MainController* mainController)
{
	Monster* leftMonster = mainController->GetLeftMonster();
	Monster* rightMonster = mainController->GetRightMonster();

	rightMonster->GetRace().GetSprite().Reverse();

	_leftParticipant = new Participant(leftMonster, 
		PositionX(0.25f), 
		PositionY(- leftMonster->GetRace().GetSprite().GetHeight() / 2, 0.7f),
		PositionX(0.25f - 1.0f / 3 / 2),
		PositionY(2, 0.7f)
	);
	_rightParticipant = new Participant(rightMonster,
		PositionX(0.75f),
		PositionY(- rightMonster->GetRace().GetSprite().GetHeight() / 2, 0.7f),
		PositionX(0.75f - 1.0f / 3 / 2),
		PositionY(2, 0.7f)
	);
	_rounds = 0;

	Console::AudioManager::Stop();
	Console::AudioManager::Play(BATTLE_MUSIC_PATH);

	mainController->InitFight();
	startFightThread(mainController);
}

void FightView::startFightThread(MainController* mainController)
{
	if (mainController->IsLeftStart())
	{
		_leftParticipant->SetAttacking(true);
		_rightParticipant->SetAttacking(false);
	}
	else
	{
		_leftParticipant->SetAttacking(false);
		_rightParticipant->SetAttacking(true);
	}

	std::thread thread([&]()
		{
			// Wait to initialize the fight scene
			Utility::sleep(1000);

			while (mainController->CanFightContinue())
			{
				_rounds++;

				// Define attacker and defender based on who is attacking
				Participant* attacker = getAttacker();
				Participant* defender = getDefender();

				attacker->PlayTurn(mainController, defender);
				
				// Wait until hp animation is finished
				waitUntilAnimationsFinished();
				Utility::sleep(500);

				attacker->ToggleAttacking();
				defender->ToggleAttacking();
			}

			Utility::sleep(1000);

			Console::AudioManager::Stop();
			Console::AudioManager::Play(MAIN_THEME_PATH);
			mainController->ClearStack();
			mainController->SetView(new VictoryView(mainController, _rounds));
		}
	);
	thread.detach();
}

void FightView::drawMonster(Console::Screen& screen, Participant* participant)
{
	screen.Draw(
		participant->GetSprite(), 
		participant->GetX().GetValue(), participant->GetY().GetValue(), 
		true, true
	);
	drawHpBar(screen, participant);
}

void FightView::drawHpBar(Console::Screen& screen, Participant* participant)
{
	// Define constants
	const int barWidth = Console::Screen::WIDTH_PIXEL / 3;
	const int currentBarWidth = static_cast<int>(static_cast<float>(barWidth) * participant->GetMonster()->GetHpPercent());
	const int yBar = participant->GetYBar().GetValue(true);
	const int xBar = participant->GetXBar().GetValue(true);

	// Draw the border of the bar
	screen.DrawRect(
		xBar - HP_BAR_BORDER_WIDTH, yBar - HP_BAR_BORDER_WIDTH, 
		barWidth + HP_BAR_BORDER_WIDTH * 2, HP_BAR_HEIGHT + HP_BAR_BORDER_WIDTH * 2, 
		BAR_BORDER_COLOR
	);

	// Draw the background of the bar
	screen.DrawRect(xBar, yBar, barWidth, HP_BAR_HEIGHT, BAR_BACK_COLOR);

	// Draw the content of the bar with a gradient of the main color
	drawBarWithGradient(screen, xBar, yBar, currentBarWidth, BAR_CONTENT_COLOR);

	if (!participant->GetHealthDifference().IsFinished())
	{
		const float currentHpDiffWidth = static_cast<float>(barWidth) * participant->GetHealthDifference().GetValue();
		const int width = static_cast<int>(currentHpDiffWidth * (1.0f - participant->GetHealthDifference().GetPercent()));
		const int xDiff = xBar + currentBarWidth;

		// Draw the difference of the hp bar with a gradient of the diff color
		drawBarWithGradient(screen, xDiff, yBar, width, BAR_CONTENT_DIFF_COLOR);
	}
}

void FightView::drawBarWithGradient(Console::Screen& screen, const int x, const int y, const int width, const std::vector<COLORREF>& colors)
{
	screen.DrawRect(
		x, y,
		width, HP_BAR_GRADIENT_HEIGHT,
		colors[0]
	);
	screen.DrawRect(
		x, y + HP_BAR_GRADIENT_HEIGHT,
		width, HP_BAR_GRADIENT_HEIGHT,
		colors[1]
	);
	screen.DrawRect(
		x, y + HP_BAR_GRADIENT_HEIGHT * 2,
		width, HP_BAR_GRADIENT_HEIGHT,
		colors[2]
	);
}

bool FightView::isAnimationsFinished() const
{
	return _leftParticipant->IsAnimationFinished() && _rightParticipant->IsAnimationFinished();
}

void FightView::updateAnimations() const
{
	_leftParticipant->UpdateAnimations();
	_rightParticipant->UpdateAnimations();
}

void FightView::waitUntilAnimationsFinished() const
{
	while (!isAnimationsFinished())
	{
		Utility::sleep(100);
	}
}

Participant* FightView::getAttacker() const
{
	return _leftParticipant->IsAttacking() ? _leftParticipant : _rightParticipant;
}

Participant* FightView::getDefender() const
{
	return _leftParticipant->IsAttacking() ? _rightParticipant : _leftParticipant;
}

void FightView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(controller->CurrentFPS), .X = 1, .Y = 1 });

	screen.Draw(Console::Text{ .Str = "Round " + std::to_string(_rounds), .X = Console::Screen::WIDTH / 2, .Y = 2, .XCentered = true });

	drawMonster(screen, _leftParticipant);
	drawMonster(screen, _rightParticipant);

	updateAnimations();
}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}
