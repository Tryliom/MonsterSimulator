#include "IntField.h"

std::string Console::IntField::GetStr() const
{	
	return "<" + _str + ">";
}

Console::IntField::IntField(std::function<int(Screen)> getX, std::function<int(Screen)> getY, const std::function<int()>& getValue,
                            const std::function<void(int)>& setValue, const bool xCentered, const bool enableLeftRightArrow) :
	BasicField(getX, getY, [getValue]() { return std::to_string(getValue()); }, [setValue](const std::string& str) { setValue(std::stoi(str)); }, 
	           IsDigit, xCentered, false)
{
	_enableLeftRightArrow = enableLeftRightArrow;
}

void Console::IntField::OnKeyPress(Controller* controller, const char key)
{
	BasicField::OnKeyPress(key);

	if (_enableLeftRightArrow) 
	{
		if (key == Key::Left)
		{
			_str = std::to_string(std::stoi(_str) - 1);
		}
		else if (key == Key::Right)
		{
			_str = std::to_string(std::stoi(_str) + 1);
		}
	}
}
