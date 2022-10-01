#include "InteractiveObject.h"

#include <utility>

namespace Console {
	InteractiveObject::InteractiveObject(std::string str, const int x, const int y, const bool xCentered, const Background background,
									const Foreground foreground, const Background selectedBackground, const Foreground selectedForeground)
	{
		_str = std::move(str);
		_x = x;
		_y = y;
		_xCentered = xCentered;
		_background = background;
		_foreground = foreground;
		_selectedBackground = selectedBackground;
		_selectedForeground = selectedForeground;
	}

	void InteractiveObject::Draw(Screen screen)
	{
		if (this->_selected)
		{
			screen.Draw(Text{ .Str = _str, .X = _x, .Y = _y, .XCentered = _xCentered, .Background = _selectedBackground, .Foreground = _selectedForeground });
		}
		else
		{
			screen.Draw(Text{ .Str = _str, .X = _x, .Y = _y, .XCentered = _xCentered, .Background = _background, .Foreground = _foreground });
		}
	}

	BasicButton::BasicButton(const std::string& str, const int x, const int y, const bool xCentered, const bool yCentered) :
		InteractiveObject(str, x, y, xCentered, Background::NONE, Foreground::NONE, Background::CYAN, Foreground::BLACK)
	{
		_yCentered = yCentered;
	}

	void BasicButton::Draw(Screen screen)
	{
		auto background = _background;
		auto foreground = _foreground;

		int y = _y;
		if (_yCentered)
		{
			y -= 1;
		}

		// Draw a border around the button
		std::string border;
		for (int i = 0; i < static_cast<int>(_str.length()) + 2; i++)
		{
			border += BORDER_ROW;
		}

		std::string text = BORDER_COLUMN + _str + BORDER_COLUMN;

		if (this->_selected)
		{
			background = _selectedBackground;
			foreground = _selectedForeground;
		}
		screen.Draw(Text{ .Str = border, .X = _x, .Y = y, .Background = background, .Foreground = foreground });
		screen.Draw(Text{ .Str = text, .X = _x, .Y = y + 1, .XCentered = _xCentered, .Background = _background, .Foreground = _foreground });
		screen.Draw(Text{ .Str = border, .X = _x, .Y = y + 2, .XCentered = _xCentered, .Background = _background, .Foreground = _foreground });
	}
}