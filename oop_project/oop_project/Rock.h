#pragma once
//---- include section ------
#include "StaticCharacter.h"
#include <string>

//---- using section --------
using std::string;

/*
 * Rock class
 */
class Rock :
	public StaticCharacter
{
public:
	// rock shape
	static const char ROCK_SHAPE = '@';
	// rock draw priority
	static const int ROCK_DRAW_PRIORITY = 8;
	// constructor
	Rock(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0),
		 const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// constructor
	Rock(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0),
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

