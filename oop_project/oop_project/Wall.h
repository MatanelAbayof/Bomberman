#pragma once
//---- include section ------
#include "StaticCharacter.h"

/*
 * Wall class
 */
class Wall :
	public StaticCharacter
{
public:
	// wall shape
	static const char WALL_SHAPE = '#';
	// wall draw priority
	static const int WALL_DRAW_PRIORITY = 30;
	// constructors
	Wall(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0),
		 const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	Wall(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0),
		 const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// convert to string
	virtual string toString() const override;
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
	// init
	void init();
};

