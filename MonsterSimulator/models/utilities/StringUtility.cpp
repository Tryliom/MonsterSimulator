#include "StringUtility.h"

namespace StringUtility
{
	// Returns a string with the first letter capitalized
	std::string Capitalize(std::string str)
	{
		if (str.length() > 0)
		{
			str[0] = toupper(str[0]);
		}
		return str;
	}
}