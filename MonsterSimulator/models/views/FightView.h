#pragma once
#include "../controllers/MainController.h"

constexpr COLORREF BAR_CONTENT_COLOR = RGB(200, 50, 50);
constexpr COLORREF BAR_CONTENT_DIFF_COLOR = RGB(170, 20, 20);
constexpr COLORREF BAR_BACK_COLOR = RGB(100, 100, 100);
constexpr COLORREF BAR_BORDER_COLOR = RGB(50, 50, 50);
const std::string BATTLE_MUSIC_PATH = "assets/audio/battle/cynthia.wav";

class FightView : public Console::View
{
private:
	Monster* _leftMonster;
	Monster* _rightMonster;
	int _rounds;

	void startFightThread(MainController* mainController);
	void drawMonster(Console::Screen& screen, const Monster* monster) const;
	static void drawHpBar(Console::Screen& screen, const Monster* monster, int x, int y);
public:
	explicit FightView(MainController* mainController);
	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

