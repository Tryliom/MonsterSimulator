#pragma once
#include <stack>

#include "../view/Screen.h"

namespace ConsoleViewController
{
	class View;

	class Controller
	{
	protected:
		Screen _screen;
		bool _canPressKey{ true };
		// The current view
		View* _view{ nullptr };
		// The previous views
		std::stack<View*> _views;

		/**
		 * \brief Used to draw things on the screen before rendering
		 */
		virtual void update();
		/**
		 * \brief Called when a key is pressed
		 * \param key The key pressed
		 */
		virtual void onKeyPressed(char key);
	private:
		/**
		 * \brief Refresh screen rendering
		 */
		void refresh();
		/**
		 * \brief Start a thread to update the screen
		 */
		void startRenderingThread();
	public:
		int CurrentFPS{ 0 };
		int Tick{ 0 };
		/**
		 * \brief Start the controller
		 */
		void Start();
		/**
		 * \brief Switch to a new view
		 * \param view The new view
		 */
		void ChangeView(View* view);
		/**
		 * \brief Go back to previous view
		 */
		void GoBack();
	};
}

