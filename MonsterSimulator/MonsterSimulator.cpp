#include "models/controllers/MainController.h"

int main()
{
	Console::Screen::EnableVirtualTerminalProcessing();
	Console::Screen::SetWindowSize(1000, 700);
	Console::Screen::SetTitle("Monster Simulator");
	Console::Screen::CenterWindow();

	/*double tenPercentOfPi = std::numbers::pi / 10.0;

	for (double i = 0; i < std::numbers::pi; i += tenPercentOfPi)
	{
		std::cout << "i = " << sin(i) << std::endl;
	}*/

	MainController controller;
	controller.Start();
}
