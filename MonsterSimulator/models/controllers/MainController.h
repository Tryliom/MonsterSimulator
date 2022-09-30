#pragma once
#include "../../lib/ConsoleViewController.h"
#include "../monster/Monster.h"

class MainController : public Console::Controller
{
private:
	Monster* _leftMonster{ nullptr };
	Monster* _rightMonster{ nullptr };

protected:
	void update() override;
	void onKeyPressed(char key) override;

public:
	MainController();

	Monster* GetLeftMonster() const { return _leftMonster; }
	Monster* GetRightMonster() const { return _rightMonster; }
	void SetLeftMonster(Monster* monster) { _leftMonster = monster; }
	void SetRightMonster(Monster* monster) { _rightMonster = monster; }
	bool CanStart() const { return _leftMonster != nullptr && _rightMonster != nullptr; }
};

