#pragma once
#include "../Screen.h"
#include "../../Constants.h"

#include <functional>

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
		virtual void OnKeyPress(const int key) = 0;
	};

	class BasicButton : public InteractiveObject
	{
	private:
		std::string _str{};
		bool _yCentered{ false };
		std::function<void()> _onClick{};
		std::string _rowBorder{ "|" };
		std::string _columnBorder{ "-" };

	public:
		BasicButton(const std::string& str, int x, int y, const std::function<void()>& onClick, bool xCentered = false, bool yCentered = false);

		void SetOnClick(std::function<void()> onClick) { _onClick = std::move(onClick); }
		void Draw(Screen screen, bool selected) override;
		void OnKeyPress(const int key) override;
	};
}


