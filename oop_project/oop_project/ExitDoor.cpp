//---- include section ------
#include "ExitDoor.h"
#include "Resources.h"

ExitDoor::ExitDoor(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, EXIT_DOOR_DRAW_PRIORITY, relPos, relSize)
{
	init();
}

ExitDoor::ExitDoor(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, EXIT_DOOR_DRAW_PRIORITY, cell, relSize)
{
	init();
}

string ExitDoor::toString() const
{
	return "ExitDoor: " + StaticCharacter::toString();
}

std::unique_ptr<Character> ExitDoor::clone()
{
	return std::make_unique<ExitDoor>(*this);
}

void ExitDoor::onCollide(Character& character)
{
	character.onCollide(*this);
}

void ExitDoor::onCollide(Guard & character)
{
}

void ExitDoor::onCollide(Player & character)
{
}

void ExitDoor::onCollide(Wall & character)
{
}

void ExitDoor::onCollide(Bomb & character)
{
}

void ExitDoor::onCollide(Rock & character)
{
}

void ExitDoor::onCollide(ExitDoor & character)
{
}

void ExitDoor::onCollide(Gift & character)
{
}

void ExitDoor::onCollide(BlowingUpBomb & character)
{
}

void ExitDoor::init()
{
	setImage(ImageTexture(Resources::Images::ExitDoor));
}
