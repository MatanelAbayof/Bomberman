#pragma once
//---- include section ------
#include "Character.h"
#include <string>

//---- using section --------
using std::string;

/*
 * StaticCharacter class
 */
class StaticCharacter :
	public Character
{
public:
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	StaticCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority = MINIMUM_PRIORITY,
		            const sf::Vector2f& relPos = sf::Vector2f(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	StaticCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority = MINIMUM_PRIORITY,
		            const Cell& cell = Cell(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0));
};

