#pragma once
#include "../../lib/ConsoleViewController.h"

class MainController : public ConsoleViewController::Controller
{
protected:
	void update() override;
	void onKeyPressed(char key) override;

public:
	MainController();
};

