//---- include section ------
#include "StaticCharacter.h"

StaticCharacter::StaticCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority,
	                             const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: Character(window, levelScreen, drawPriority, relPos, relSize)
{ }

StaticCharacter::StaticCharacter(sf::RenderWindow & window, LevelScreen & levelScreen, int drawPriority,
	                             const Cell & cell, const sf::Vector2f & relSize)
	: Character(window, levelScreen, drawPriority, cell, relSize)
{ }

string StaticCharacter::toString() const
{
	return "StaticCharacter: " + Character::toString();
}
