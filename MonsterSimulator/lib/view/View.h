#pragma once
#include "screen.h"
#include "../controller/Controller.h"

namespace Console
{
	class Controller;

	class View
	{
	private:
		int _currentButton{ 0 };
		int _maxButtons{ 0 };
	public:
		View(int defaultButton = 0, int maxButton = 0);
		/**
		 * \brief Call before the render function to prepare the screen
		 * \param controller The controller to get the data from
		 * \param screen The screen to draw on
		 */
		virtual void Update(Controller* controller, Screen& screen) = 0;
		/**
		 * \brief Call when the user press a key, need to be call at the end of the Update function to correct the button selection
		 * \param controller The controller to get the data from
		 * \param key The key pressed
		 */
		virtual void OnKeyPressed(Controller* controller, char key);

		int GetMaxButton() const { return _maxButtons; }
		void SetCurrentButton(const int currentButton) { _currentButton = currentButton; }
		void IncrementCurrentButton() { _currentButton++; }
		void DecrementCurrentButton() { _currentButton--; }
		void SetMaxButton(const int maxButton) { _maxButtons = maxButton; }
		int GetCurrentButton() const { return _currentButton; }
	};
}


