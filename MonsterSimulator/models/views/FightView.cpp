#include "FightView.h"

FightView::FightView(MainController* mainController)
{

}

void FightView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);


}

void FightView::OnKeyPressed(Console::Controller* controller, const char key)
{


	View::OnKeyPressed(controller, key);
}
