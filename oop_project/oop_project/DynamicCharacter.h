#pragma once
//---- include section ------
#include <string>
#include "Character.h"

//---- using section --------
using std::string;

/*
 * DynamicCharacter class
 */
class DynamicCharacter :
	public Character
{
public:
	// number of directions
	static const int NUM_OF_DIRECTIONS = 4;
	// moving direction
	enum Direction {
		RIGHT, LEFT, UP, DOWN, STANDING
	};
	// minimum speed
	static const float MINIMUM_SPEED;
	// set speed
	void setSpeed(float speed);
	// append speed
	void appendSpeed(float speed);
	// get speed
	float getSpeed() const;
	// has no speed
	bool hasNoSpeed() const;
	// set direction
	virtual void setDirection(Direction direction);
	// get direction
	Direction getDirection() const;
	// move (by relative position)
	void move(const sf::Vector2f& relativePosition);
	void move(float x, float y);
	// check if character can move to position
	virtual bool canMove(const sf::Vector2f& relativePosition);
	// play
	virtual void play() = 0;
	// draw
	virtual void draw();
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	DynamicCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority = MINIMUM_PRIORITY, 
		const sf::Vector2f& relPos = sf::Vector2f(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0), float speed = MINIMUM_SPEED);
	// constructor
	DynamicCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority = MINIMUM_PRIORITY,
		const Cell& cell = Cell(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0), float speed = MINIMUM_SPEED);
	// calculate next position by clock, speed and direction
	sf::Vector2f requestNextPosition();
	// check if character in my collide movement
	bool isCharInMyCollideM(const Character& character) const;
	// add collide character type name
	void addCollideCharacterType(const string& charType);
private:
	// collide characters
	std::vector<string> m_collideCharacters;
	// clock (for update position)
	sf::Clock m_clock;
	// speed (unit: number of cells / seconds)
	float m_speed;
	// direction
	Direction m_direction;
	// check if speed is legal
	bool isLegalSpeed(float speed) const;
	// convert direction to string
	string directionToStr(Direction direction) const;
	// check collides character in my cell
	bool isCharsInCellCollide(const Cell& cell, const sf::FloatRect& bounds);
};