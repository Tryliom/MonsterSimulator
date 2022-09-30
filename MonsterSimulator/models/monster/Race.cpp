#include "Race.h"

Race::Race(const RaceType type, const std::string& name, const bool reverseSprite)
{
	_type = type;
	_name = name;
	_sprite = Console::Image("assets/images/races/" + _name + ".txt");

	if (reverseSprite)
	{
		_sprite.Reverse();
	}
}
