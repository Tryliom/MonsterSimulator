#pragma once
#include "screen.h"
#include "../controller/Controller.h"

namespace ConsoleViewController
{
	class Controller;

	class View
	{
	public:
		/**
		 * \brief Call before the render function to prepare the screen
		 * \param controller The controller to get the data from
		 * \param screen The screen to draw on
		 */
		virtual void Update(Controller* controller, Screen& screen) = 0;
		/**
		 * \brief Call when the user press a key
		 * \param controller The controller to get the data from
		 * \param key The key pressed
		 */
		virtual void OnKeyPressed(Controller* controller, char key) = 0;
	};
}


