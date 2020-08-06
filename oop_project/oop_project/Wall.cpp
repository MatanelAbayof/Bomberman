//---- include section ------
#include "Wall.h"
#include "Resources.h"

Wall::Wall(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos,
	       const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, WALL_DRAW_PRIORITY, relPos, relSize)
{
	init();
}

Wall::Wall(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell, 
	       const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, WALL_DRAW_PRIORITY, cell, relSize)
{
	init();
}

string Wall::toString() const
{
	return "Wall: " + StaticCharacter::toString();
}

std::unique_ptr<Character> Wall::clone()
{
	return std::make_unique<Wall>(*this);
}

void Wall::onCollide(Character & character)
{
	character.onCollide(*this);
}

void Wall::onCollide(Guard & character)
{
}

void Wall::onCollide(Player & character)
{
}

void Wall::onCollide(Wall & character)
{
}

void Wall::onCollide(Bomb & character)
{
}

void Wall::onCollide(Rock & character)
{
}

void Wall::onCollide(ExitDoor & character)
{
}

void Wall::onCollide(Gift & character)
{
}

void Wall::onCollide(BlowingUpBomb & character)
{
}

void Wall::init()
{
	setImage(ImageTexture(Resources::Images::Wall));
}
