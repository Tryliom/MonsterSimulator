#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../fight/Participant.h"

#include <vector>

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

namespace RenderUtility
{
	void DrawMonster(Console::Screen& screen, Participant* participant);
	void DrawHpBar(Console::Screen& screen, Participant* participant);
	void DrawBarWithGradient(Console::Screen& screen, const int x, const int y, const int width, const std::vector<COLORREF>& colors);
};

