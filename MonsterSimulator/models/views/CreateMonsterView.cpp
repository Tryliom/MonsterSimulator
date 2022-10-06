#include "CreateMonsterView.h"
#include "MenuView.h"
#include "../utilities/StringUtility.h"

CreateMonsterView::CreateMonsterView(const MainController* mainController, const bool left) : View()
{
	_left = left;
	if (left)
	{
		_otherMonster = mainController->GetRightMonster();
	}
	else
	{
		_otherMonster = mainController->GetLeftMonster();
	}

	std::vector<std::string> races;

	races.reserve(RACES.size());
	for (const Race* race: RACES)
	{
		races.emplace_back(StringUtility::Capitalize(race->GetName()));
	}

	setComponents({
		new Console::Selector(PositionX(0.5f), PositionY(5), races,
		[this](const int index) {this->_raceSelected = index; }),
		new Console::IntField(PositionX(0.5f), PositionY(7), [this]() {return _hp; }, [this](const int value) {_hp = value; }),
		new Console::IntField(PositionX(0.5f), PositionY(9), [this]() {return _attack; }, [this](const int value) {_attack = value; }),
		new Console::IntField(PositionX(0.5f), PositionY(11), [this]() {return _armor; }, [this](const int value) {_armor = value; }),
		new Console::IntField(PositionX(0.5f), PositionY(13), [this]() {return _speed; }, [this](const int value) {_speed = value; }),
		new Console::BasicButton("Create", PositionX(0.5f), PositionY(16), [this](Console::Controller* controller) {this->createMonster(controller); }, true)
	});
}

void CreateMonsterView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	// Draw the title of the view
	screen.Draw(Console::Text{ .Str = "Monster Creator", .X = Console::Screen::WIDTH / 2, .Y = 2, .XCentered = true });
	int y = 5;
	// Draw Race field
	screen.Draw(Console::Text{ .Str = "Race:", .X = Console::Screen::WIDTH / 4, .Y = y });
	y += 2;
	// Draw Hp field
	screen.Draw(Console::Text{ .Str = "Hp:", .X = Console::Screen::WIDTH / 4, .Y = y });
	y += 2;
	// Draw Attack field
	screen.Draw(Console::Text{ .Str = "Attack:", .X = Console::Screen::WIDTH / 4, .Y = y });
	y += 2;
	// Draw Armor field
	screen.Draw(Console::Text{ .Str = "Armor:", .X = Console::Screen::WIDTH / 4, .Y = y });
	y += 2;
	// Draw Speed field
	screen.Draw(Console::Text{ .Str = "Speed:", .X = Console::Screen::WIDTH / 4, .Y = y });
	y += 3;
	// Draw the error message
	screen.Draw(Console::Text{ .Str = _errorMessage, .X = Console::Screen::WIDTH / 2, .Y = y + 5, .XCentered = true, .Foreground = Console::Foreground::RED });

	// Display controls for the user
	screen.Draw(Console::Text{ .Str = "Exit: Esc | Left & right: select/change numbers | Up & down: move | Confirm: Enter", .X = Console::Screen::WIDTH / 2, 
		.Y = Console::Screen::HEIGHT - 3, .XCentered = true });
}

void CreateMonsterView::OnKeyPressed(Console::Controller* controller, const char key)
{
	_errorMessage.clear();

	if (key == Console::Key::Down)
	{
		IncrementCurrentButton();
	}
	else if (key == Console::Key::Up)
	{
		DecrementCurrentButton();
	}

	View::OnKeyPressed(controller, key);
}

void CreateMonsterView::createMonster(Console::Controller* controller)
{
	_race = RACES[_raceSelected];

	if (_hp <= 0 || _attack <= 0 || _armor <= 0 || _speed <= 0)
	{
		_errorMessage = "All stats must be greater than 0";
	}
	else if (_otherMonster != nullptr && _otherMonster->GetRace().GetName() == _race->GetName())
	{
		_errorMessage = "The race of the monster can't be the same than the other";
	}
	else
	{
		const auto mainController = static_cast<MainController*>(controller);
		const auto monster = new Monster(*_race, _hp, _attack, _armor, _speed);

		if (_left)
		{
			mainController->SetLeftMonster(monster);
		}
		else
		{
			mainController->SetRightMonster(monster);
		}
		mainController->ClearStack();
		mainController->SetView(new MenuView(mainController));
	}
}