#include "MainController.h"
#include "../views/MenuView.h"

MainController::MainController()
{
	ChangeView(new MenuView(this));
}
