#include "FightView.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "VictoryView.h"
#include "../utilities/RenderUtility.h"

#include <thread>
#include <numbers>

FightView::FightView(MainController* mainController)
{
	Monster* leftMonster = mainController->GetLeftMonster();
	Monster* rightMonster = mainController->GetRightMonster();

	rightMonster->GetRace().GetSprite().Reverse();

	_leftParticipant = new Participant(leftMonster, true);
	_rightParticipant = new Participant(rightMonster, false);
	_rounds = 0;

	Console::AudioManager::Stop();
	if (leftMonster->GetRace().GetRaceType() == RaceType::ARCEUS || rightMonster->GetRace().GetRaceType() == RaceType::ARCEUS)
	{
		Console::AudioManager::Play(SPECIAL_BATTLE_MUSIC_PATH, true);
	}
	else
	{
		Console::AudioManager::Play(BATTLE_MUSIC_PATH, true);
	}

	mainController->FullHeal();
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
			Console::Screen::PIXEL_CACHE = false;
			// Wait for the hp bar to get correctly drawn
			Utility::sleep(2000);

			Console::Screen::PIXEL_CACHE = true;

			while (mainController->CanFightContinue())
			{
				_rounds++;

				// Define attacker and defender based on who is attacking
				Participant* attacker = getAttacker();
				Participant* defender = getDefender();

				attacker->PlayTurn(mainController, defender);
				
				// Wait until hp animation is finished
				waitUntilAnimationsFinished();

				// Wait 1.5sec before the next turn
				Utility::sleep(1500);

				attacker->ToggleAttacking();
				defender->ToggleAttacking();
			}

			Utility::sleep(1000);

			_rightParticipant->GetMonster()->GetRace().GetSprite().Reverse();

			Console::AudioManager::Stop();
			Console::AudioManager::Play(MAIN_THEME_PATH, true);

			mainController->ClearStack();
			mainController->SetView(new VictoryView(mainController, _rounds));
		}
	);
	thread.detach();
}

bool FightView::isAnimationsFinished() const
{
	return _leftParticipant->IsAnimationFinished() && _rightParticipant->IsAnimationFinished();
}

void FightView::waitUntilAnimationsFinished() const
{
	while (!isAnimationsFinished()) {}
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

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(Console::Controller::FPS), .X = 1, .Y = 1 });

	screen.Draw(Console::Text{ .Str = "Round " + std::to_string(_rounds), .X = Console::Screen::WIDTH / 2, .Y = 2, .XCentered = true });

	RenderUtility::DrawMonster(screen, _leftParticipant);
	RenderUtility::DrawMonster(screen, _rightParticipant);
}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{
	View::OnKeyPressed(controller, key);
}

void FightView::OnTick(Console::Controller* controller, const int deltaTime)
{
	_leftParticipant->UpdateAnimations(deltaTime);
	_rightParticipant->UpdateAnimations(deltaTime);
}
