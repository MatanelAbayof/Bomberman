//---- include section ------
#include "StupidGuard.h"

StupidGuard::StupidGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos,
	                     const sf::Vector2f& relSize)
		: Guard(window, levelScreen, relPos, relSize)
{
	init();
}

StupidGuard::StupidGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell,
	                     const sf::Vector2f& relSize)
	: Guard(window, levelScreen, cell, relSize)
{
	init();
}

void StupidGuard::play()
{
	sf::Vector2f nextPosition = requestNextPosition();
	if (canMove(nextPosition))
		setRelativePosition(nextPosition);
	else
		setDirection(getRandomDirect());
}

string StupidGuard::toString() const
{
	return string("StupidGuard: " + DynamicCharacter::toString());
}

std::unique_ptr<Character> StupidGuard::clone()
{
	return std::make_unique<StupidGuard>(*this);
}

void StupidGuard::init()
{
	setSpeed(DEFAULT_SPEED);
}
