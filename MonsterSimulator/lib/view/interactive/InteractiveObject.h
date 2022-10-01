#pragma once
#include <functional>

#include "../Screen.h"

namespace Console
{
	class InteractiveObject
	{
	protected:
		std::string _str{};
		int _x{ 0 };
		int _y{ 0 };
		bool _xCentered{ false };
		Background _background{ Background::NONE };
		Foreground _foreground{ Foreground::NONE };
		bool _selected{ false };
		Background _selectedBackground{ Background::CYAN };
		Foreground _selectedForeground{ Foreground::BLACK };

	public:
		InteractiveObject(std::string str, int x, int y, bool xCentered = false, Background background = Background::NONE, Foreground foreground = Foreground::NONE,
			Background selectedBackground = Background::CYAN, Foreground selectedForeground = Foreground::BLACK);

		void SetSelected(const bool selected) { _selected = selected; }
		bool IsSelected() const { return _selected; }

		virtual void Draw(Screen screen);
	};

	struct BasicButton : public InteractiveObject
	{
	private:
		bool _yCentered{ false };
		std::function<void()> _onClick{};

	public:
		BasicButton(const std::string& str, int x, int y, bool xCentered = false, bool yCentered = false);

		void SetOnClick(std::function<void()> onClick) { _onClick = std::move(onClick); }
		void Draw(Screen screen) override;
	};
}


