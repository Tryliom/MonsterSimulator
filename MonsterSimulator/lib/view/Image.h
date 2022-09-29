#pragma once
#include <map>
#include <string>
#include <vector>

const std::map<std::string, std::string> REVERSE_CHARS = {
	{"/", "\\"},
	{"\\", "/"},
	{"{", "}"},
	{"}", "{"},
	{"(", ")"},
	{")", "("},
	{"[", "]"},
	{"]", "["},
	{"<", ">"},
	{">", "<"},
	{"J", "L"},
	{"L", "J"},
	{"E", "3"},
	{"3", "E"},
	{"2", "S"},
	{"S", "2"}
};

namespace ConsoleViewController
{
	class Image
	{
	private:
		std::vector<std::string> _image;
		int _width{ 0 };
		int _height{ 0 };

	public:
		Image() = default;
		explicit Image(const std::string& path);

		std::vector<std::string> GetImage() const { return this->_image; }
		int GetWidth() const { return this->_width; }
		int GetHeight() const { return this->_height; }

		void Reverse();
	};
}
