#pragma once
#include "controller/Controller.h"
#include "view/View.h"
#include "view/Screen.h"

namespace ConsoleViewController
{
#pragma region constants

	int constexpr FPS = 60;
	bool constexpr LIMIT_FPS = true;
	// Useful key codes
	constexpr auto KEY_UP = 72;
	constexpr auto KEY_DOWN = 80;
	constexpr auto KEY_LEFT = 75;
	constexpr auto KEY_RIGHT = 77;
	constexpr auto KEY_ENTER = 13;
	constexpr auto KEY_ESC = 27;
	constexpr auto KEY_BACKSPACE = 8;

#pragma endregion
}