#pragma once
#include "../controllers/MainController.h"

#pragma region Battle constants
	constexpr COLORREF BAR_CONTENT_COLOR1 = RGB(220, 70, 70);
	constexpr COLORREF BAR_CONTENT_COLOR2 = RGB(200, 50, 50);
	constexpr COLORREF BAR_CONTENT_COLOR3 = RGB(180, 40, 40);
	constexpr COLORREF BAR_CONTENT_DIFF_COLOR1 = RGB(175, 25, 25);
	constexpr COLORREF BAR_CONTENT_DIFF_COLOR2 = RGB(170, 20, 20);
	constexpr COLORREF BAR_CONTENT_DIFF_COLOR3 = RGB(165, 15, 15);
	constexpr COLORREF BAR_BACK_COLOR = RGB(100, 100, 100);
	constexpr COLORREF BAR_BORDER_COLOR = RGB(50, 50, 50);
	const std::string BATTLE_MUSIC_PATH = "assets/audio/battle/cynthia.wav";
#pragma endregion

struct Animation
{
	int Value;
	int CurrentDuration;
	int Duration;

	Animation(const int value, const int duration) : Value(value), CurrentDuration(0), Duration(duration) {}

	bool IsFinished() { return CurrentDuration >= Duration; }
	void Update() { if (!IsFinished()) CurrentDuration++; }
	float GetPercent() const { return static_cast<float>(CurrentDuration) / static_cast<float>(Duration); }
};

struct Participant
{
	Monster* Monster{ nullptr };
	Animation HpDiff{ Animation(0, 0) };
	Animation AttackAnimation{ Animation(0, 0) };

	Participant(class Monster* monster)
	{
		Monster = monster;
	}
};

class FightView : public Console::View
{
private:
	Participant* _leftParticipant;
	Participant* _rightParticipant;
	int _rounds;

	void startFightThread(MainController* mainController);
	void drawMonster(Console::Screen& screen, Participant* participant);
	void drawHpBar(Console::Screen& screen, Participant* participant, int x, int y);
public:
	explicit FightView(MainController* mainController);
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

