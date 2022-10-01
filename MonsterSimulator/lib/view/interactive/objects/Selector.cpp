#include "Selector.h"

namespace Console
{
	Selector::Selector(const int x, const int y, const std::vector<std::string>& options,
	                   const std::function<void(int)>& setValue, const bool xCentered) :
		InteractiveObject(x, y, xCentered)
	{
		_options = options;
		_setValue = setValue;
	}

	void Selector::Draw(Screen screen, const bool selected)
	{
		Background background = _background;
		Foreground foreground = _foreground;

		if (selected)
		{
			background = _selectedBackground;
			foreground = _selectedForeground;
		}

		int x = _x;
		for (int i = 0; i < static_cast<int>(_options.size()); i++)
		{
			if (i == _selected)
			{
				screen.Draw(Text{ .Str = "<" + _options[i] + ">", .X = x, .Y = _y, .XCentered = false, .Background = background, .Foreground = foreground});
			}
			else
			{
				screen.Draw(Text{ .Str = _options[i], .X = x, .Y = _y, .XCentered = false, .Background = _background, .Foreground = _foreground });
			}
			
			x += static_cast<int>(_options[i].length()) + 4;
		}
	}

	void Selector::OnKeyPress(const char key)
	{
		if (key == Key::Left)
		{
			_selected--;
		}
		else if (key == Key::Right)
		{
			_selected++;
		}

		if (_selected >= static_cast<int>(_options.size()))
		{
			_selected = static_cast<int>(_options.size()) - 1;
		}
		else if (_selected < 0)
		{
			_selected = 0;
		}

		_setValue(_selected);
	}
}
