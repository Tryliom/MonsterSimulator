#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

enum class RaceType
{
	NONE,
	DRAGON,
	ELF,
	MINOTOUR,
	PHANTOM,
	TRIBAL,
	ARCEUS
};

class Race
{
private:
	std::string _name;
	RaceType _type{RaceType::NONE};
	Console::Image _sprite;

public:
	Race() = default;
	Race(RaceType type, const std::string& name, bool reverseSprite = false);

	std::string GetName() const { return _name; }
	RaceType GetRaceType() const { return _type; }
	Console::Image& GetSprite() { return _sprite; }
};

class Dragon : public Race
{
public:
	Dragon() : Race(RaceType::DRAGON, "dragon") {}
};

class Elf : public Race
{
public:
	Elf() : Race(RaceType::ELF, "elf", true) {}
};

class Minotour : public Race
{
public:
	Minotour() : Race(RaceType::MINOTOUR, "minotour") {}
};

class Phantom : public Race
{
public:
	Phantom() : Race(RaceType::PHANTOM, "phantom") {}
};

class Tribal : public Race
{
public:
	Tribal() : Race(RaceType::TRIBAL, "tribal") {}
};

class Arceus : public Race
{
public:
	Arceus() : Race(RaceType::ARCEUS, "arceus", true) {}
};