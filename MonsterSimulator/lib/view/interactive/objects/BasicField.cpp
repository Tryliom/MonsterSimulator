#include "BasicField.h"

Console::BasicField::BasicField(const int x, const int y, const std::function<std::string()>& getValue,
                                const std::function<void(std::string)>& setValue, const std::function<bool(char key)>& condition, const bool xCentered) : InteractiveObject(x, y, xCentered)
{
	_getValue = getValue;
	_setValue = setValue;
	_condition = condition;
	_str = _getValue();
}

void Console::BasicField::Draw(Screen screen, const bool selected)
{
	auto background = _background;
	auto foreground = _foreground;

	if (selected)
	{
		background = _selectedBackground;
		foreground = _selectedForeground;
	}

	screen.Draw(Text{ .Str = _str, .X = _x, .Y = _y, .XCentered = _xCentered, .Background = background, .Foreground = foreground });

	if (_showCursor)
	{
		screen.SetCursor(_x + static_cast<int>(_str.length()), _y);
	}
}

void Console::BasicField::OnKeyPress(const char key)
{
	if (_condition(key))
	{
		onConditionValidation(key);
	}
	else if (key == Key::Backspace)
	{
		onBackspace();
	}
}

void Console::BasicField::onConditionValidation(const char key)
{
	_str += key;
	_setValue(_str);
}

void Console::BasicField::onBackspace()
{
	if (_str.length() > 0)
	{
		_str.pop_back();
		_setValue(_str);
	}
}
