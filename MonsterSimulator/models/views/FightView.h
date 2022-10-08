#pragma once
#include "../controllers/MainController.h"
#include "../fight/Participant.h"

#pragma region Battle constants
	const std::vector BAR_CONTENT_COLOR = {
		RGB(220, 70, 70),
		RGB(200, 50, 50),
		RGB(180, 40, 40)
	};
	const std::vector BAR_CONTENT_DIFF_COLOR = {
		RGB(175, 40, 40),
		RGB(170, 40, 40),
		RGB(165, 40, 40)
	};

	constexpr COLORREF BAR_BACK_COLOR = RGB(100, 100, 100);
	constexpr COLORREF BAR_BORDER_COLOR = RGB(50, 50, 50);

	constexpr int HP_BAR_HEIGHT = 15;
	constexpr int HP_BAR_BORDER_WIDTH = 4;
	constexpr int HP_BAR_GRADIENT_HEIGHT = HP_BAR_HEIGHT * 1 / 3;
#pragma endregion

class FightView : public Console::View
{
private:
	Participant* _leftParticipant;
	Participant* _rightParticipant;
	int _rounds;

	void startFightThread(MainController* mainController);

	static void drawMonster(Console::Screen& screen, Participant* participant);
	static void drawHpBar(Console::Screen& screen, Participant* participant);
	static void drawBarWithGradient(Console::Screen& screen, int x, int y, int width, const std::vector<COLORREF>& colors);

	bool isAnimationsFinished() const;
	void updateAnimations() const;
	void waitUntilAnimationsFinished() const;

	Participant* getAttacker() const;
	Participant* getDefender() const;
public:
	explicit FightView(MainController* mainController);

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

