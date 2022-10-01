#pragma once
#include "../Screen.h"
#include "../../Constants.h"

namespace Console
{
	class InteractiveObject
	{
	protected:
		int _x{ 0 };
		int _y{ 0 };
		bool _xCentered{ false };
		Background _background{ Background::NONE };
		Foreground _foreground{ Foreground::NONE };
		Background _selectedBackground{ Background::CYAN };
		Foreground _selectedForeground{ Foreground::BLACK };

	public:
		InteractiveObject(int x, int y, bool xCentered = false);

		virtual void Draw(Screen screen, bool selected) = 0;
		virtual void OnKeyPress(const char key) = 0;
	};


}


