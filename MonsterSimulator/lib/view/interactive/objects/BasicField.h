#pragma once
#include <functional>

#include "../InteractiveObject.h"

namespace Console
{
	class BasicField : public InteractiveObject
	{
	protected:
		std::string _str;
		bool _showCursor{ true };
		std::function<std::string()> _getValue;
		std::function<void(std::string)> _setValue;
		std::function<bool(char key)> _condition;

		virtual void onConditionValidation(const char key);
		virtual void onBackspace();
	public:
		BasicField(int x, int y, const std::function<std::string()>& getValue, const std::function<void(std::string)>& setValue, 
					const std::function<bool(char key)>& condition = [](char key) { return true; }, bool xCentered = false);

		inline static std::function<bool(char key)> IsDigit = [](const char key) { return key >= '0' && key <= '9'; };
		inline static std::function<bool(char key)> IsLetter = [](const char key) { return (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'); };
		inline static std::function<bool(char key)> IsSymbol = [](const char key) { return (key >= '!' && key <= '/') || (key >= ':' && key <= '@') || (key >= '[' && key <= '`') || (key >= '{' && key <= '~'); };
		inline static std::function<bool(char key)> IsSpace = [](const char key) { return key == ' '; };
		inline static std::function<bool(char key)> DefaultCondition = [](const char key) { return true; };

		void Draw(Screen screen, bool selected) override;
		void OnKeyPress(char key) override;
	};
}

