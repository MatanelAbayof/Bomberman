//---- include section ------
#include "Rock.h"
#include "Resources.h"

Rock::Rock(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, ROCK_DRAW_PRIORITY, relPos, relSize)
{
	init();
}

Rock::Rock(sf::RenderWindow & window, LevelScreen & levelScreen, const Cell & cell, const sf::Vector2f & relSize)
	: StaticCharacter(window, levelScreen, ROCK_DRAW_PRIORITY, cell, relSize)
{
	init();
}

string Rock::toString() const
{
	return "Rock: " + StaticCharacter::toString();
}

std::unique_ptr<Character> Rock::clone()
{
	return std::make_unique<Rock>(*this);
}

void Rock::onCollide(Character & character)
{
	character.onCollide(*this);
}

void Rock::onCollide(Guard& character)
{
}

void Rock::onCollide(Player& character)
{
}

void Rock::onCollide(Wall& character)
{
}

void Rock::onCollide(Bomb& character)
{
}

void Rock::onCollide(Rock& character)
{
}

void Rock::onCollide(ExitDoor& character)
{
}

void Rock::onCollide(Gift& character)
{
}

void Rock::onCollide(BlowingUpBomb& character)
{
	killMySelf();
}

void Rock::init()
{
	setImage(ImageTexture(Resources::Images::Rock));
}
