#include "RenderUtility.h"

namespace RenderUtility
{
	void DrawMonster(Console::Screen& screen, Participant* participant)
	{
		int xOffset = 0;

		// Make the sprite going forth and back when attacking
		if (!participant->GetAttackAnimation().IsFinished())
		{
			xOffset = participant->CalculateAttackXOffset();
		}

		// Add a shaking animation if he gets hit
		if (!participant->GetHealthDifference().IsFinished())
		{
			xOffset += (Console::Controller::TICK % 6) - 3;
		}

		screen.Draw(
			participant->GetSprite(),
			participant->GetX().GetValue() + xOffset, participant->GetY().GetValue(),
			true, true
		);

		DrawHpBar(screen, participant);
	}

	void DrawHpBar(Console::Screen& screen, Participant* participant)
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
		DrawBarWithGradient(screen, xBar, yBar, currentBarWidth, BAR_CONTENT_COLOR);

		if (!participant->GetHealthDifference().IsFinished())
		{
			const float healthDifference = participant->GetHealthDifference().GetValue();
			const float animationPercent = participant->GetHealthDifference().GetPercent();

			// Define proportions value according to the animation
			const float currentHpDiffWidth = static_cast<float>(barWidth) * healthDifference;
			const int width = static_cast<int>(currentHpDiffWidth * (1.0f - animationPercent));
			const int xDiff = xBar + currentBarWidth;

			// Draw the difference of the hp bar with a gradient of the diff color
			DrawBarWithGradient(screen, xDiff, yBar, width, BAR_CONTENT_DIFF_COLOR);
		}
	}

	void DrawBarWithGradient(Console::Screen& screen, const int x, const int y, const int width, const std::vector<COLORREF>& colors)
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
}
