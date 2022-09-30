#include "View.h"

namespace Console
{
	View::View(const int defaultButton, const int maxButton)
	{
		_currentButton = defaultButton;
		_maxButtons = maxButton;
	}

	void View::OnKeyPressed(Controller* controller, const char key)
	{
		if (_maxButtons == 0)
			return;

		if (_currentButton >= _maxButtons)
		{
			_currentButton = _maxButtons - 1;
		}
		if (_currentButton < 0)
		{
			_currentButton = 0;
		}
	}
}