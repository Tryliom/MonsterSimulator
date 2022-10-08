#include "MonsterEditorView.h"
#include "MenuView.h"
#include "../utilities/StringUtility.h"

MonsterEditorView::MonsterEditorView(Monster* monster) : View()
{
	_monster = monster;

	if (monster->GetRace().GetRaceType() == RaceType::NONE)
	{
		monster->SetRace(*RACES[0]);
	}

	std::vector<std::string> races;
	races.reserve(RACES.size());

	int i = 0;
	int defaultSelectedRace = 0;
	for (const Race* race: RACES)
	{
		if (race->GetRaceType() == _monster->GetRace().GetRaceType())
		{
			defaultSelectedRace = i;
		}
		races.emplace_back(StringUtility::Capitalize(race->GetName()));
		i++;
	}

	setComponents({
		new Console::Selector(PositionX(0.5f), PositionY(5), races,
		[this](const int index) {_monster->SetRace(*RACES[index]); }, defaultSelectedRace),
		new Console::IntField(
			PositionX(0.5f), PositionY(7), 
		[this]() {return _monster->GetHp(); }, 
		[this](const int value) {_monster->SetHp(value); }
		),
		new Console::IntField(
			PositionX(0.5f), PositionY(9), 
			[this]() {return _monster->GetAttack(); }, 
			[this](const int value) {_monster->SetAttack(value); }
		),
		new Console::IntField(
			PositionX(0.5f), PositionY(11), 
			[this]() {return _monster->GetArmor(); }, 
			[this](const int value) {_monster->SetArmor(value); }
		),
		new Console::IntField(
			PositionX(0.5f), PositionY(13), 
			[this]() {return _monster->GetSpeed(); }, 
			[this](const int value) {_monster->SetSpeed(value); }
		),
		new Console::BasicButton("Create", PositionX(0.5f), PositionY(16), [this](Console::Controller* controller) {this->createMonster(controller); }, true)
	});
}

void MonsterEditorView::Update(Console::Controller* controller, Console::Screen& screen)
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
	screen.Draw(Console::Text{
		.Str = "Back & save: Esc | Left & right: select/change numbers | Up & down: move | Confirm: Enter", 
		.X = Console::Screen::WIDTH / 2, .Y = Console::Screen::HEIGHT - 3, .XCentered = true
	});
}

void MonsterEditorView::OnKeyPressed(Console::Controller* controller, const char key)
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

void MonsterEditorView::createMonster(Console::Controller* controller)
{
	if (_monster->GetHp() <= 0 || _monster->GetAttack() <= 0 || _monster->GetArmor() <= 0 || _monster->GetSpeed() <= 0)
	{
		_errorMessage = "All stats must be greater than 0";
	}
	else
	{
		const auto mainController = static_cast<MainController*>(controller);
		mainController->ClearStack();
		mainController->SetView(new MenuView(mainController));
	}
}