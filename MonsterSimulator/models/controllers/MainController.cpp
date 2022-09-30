#include "MainController.h"
#include "../views/MenuView.h"


void MainController::update()
{
	Controller::update();
}

void MainController::onKeyPressed(const char key)
{
	Controller::onKeyPressed(key);
}

MainController::MainController()
{
	ChangeView(new MenuView());
}
