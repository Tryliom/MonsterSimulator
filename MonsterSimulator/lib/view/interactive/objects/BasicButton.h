#pragma once
#include "../InteractiveObject.h"

#include <functional>

namespace Console
{
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
		
		void Draw(Screen screen, bool selected) override;
		void OnKeyPress(int key) override;
	};
}

