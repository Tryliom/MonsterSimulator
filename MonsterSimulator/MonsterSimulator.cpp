#include "models/controllers/MainController.h"

int main()
{
	Console::Screen::SetWindowSize(1000, 700);
	Console::Screen::SetTitle("Monster Simulator");
	Console::Screen::CenterWindow();

	MainController controller;
	controller.Start();
}
