#pragma once
//---- include section ------
#include "Guard.h"
#include <string>

//---- using section --------
using std::string;

/*
 * StupidGuard class
 */
class StupidGuard :
	public Guard
{
public:
	// constructors
	StupidGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0),
		        const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	StupidGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0),
		        const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// play
	virtual void play() override;
	// convert to string
	virtual string toString() const override;
	// make unique ptr
	virtual std::unique_ptr<Character> clone() override;
private:
	// default speed
	const float DEFAULT_SPEED = 1.5f;
	// init
	void init();
};

