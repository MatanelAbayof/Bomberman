#pragma once
//---- include section ------
#include "StaticCharacter.h"
#include <string>

//---- using section --------
using std::string;

/*
 * ExitDoor class
 */
class ExitDoor :
	public StaticCharacter
{
public:
	// exit door shape
	static const char EXIT_DOOR_SHAPE = 'D';
	// exit door draw priority
	static const int EXIT_DOOR_DRAW_PRIORITY = 3;
	// constructors
	ExitDoor(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0), 
		     const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	ExitDoor(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0), 
		     const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// convert to string
	virtual string toString() const;
	// make unique ptr
	virtual std::unique_ptr<Character> clone() override;
	// collide events
	virtual void onCollide(Character& character) override;
	virtual void onCollide(Guard& character) override;
	virtual void onCollide(Player& character) override;
	virtual void onCollide(Wall& character) override;
	virtual void onCollide(Bomb& character) override;
	virtual void onCollide(Rock& character) override;
	virtual void onCollide(ExitDoor& character) override;
	virtual void onCollide(Gift& character) override;
	virtual void onCollide(BlowingUpBomb& character) override;
private:
	//init
	void init();
};

