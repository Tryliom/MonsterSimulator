#pragma once
#include "../controllers/MainController.h"
#include "../fight/Participant.h"

// Used to display a fight between two monsters
class FightView : public Console::View
{
private:
	Participant* _leftParticipant;
	Participant* _rightParticipant;
	int _rounds;

	void startFightThread(MainController* mainController);

	bool isAnimationsFinished() const;
	void waitUntilAnimationsFinished() const;

	Participant* getAttacker() const;
	Participant* getDefender() const;
public:
	explicit FightView(MainController* mainController);

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
	void OnTick(Console::Controller* controller, int deltaTime) override;
};

