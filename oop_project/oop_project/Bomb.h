#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "StaticCharacter.h"
#include "StopWatch.h"
#include <string>

//---- using section --------
using std::string;

/*
 * Bomb class
 */
class Bomb :
	public StaticCharacter
{
public:
	// Bomb draw priority
	static const int BOMB_DRAW_PRIORITY = 10;
	// constructors
	Bomb(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0), 
		 const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	Bomb(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0), 
		 const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// copy constructor
	Bomb(Bomb& anotherBomb);
	// convert to string
	virtual string toString() const;
	// make unique ptr
	virtual std::unique_ptr<Character> clone() override;
	// draw
	virtual void draw();
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
	// stop Watch
	StopWatch m_stoper;
	// bomb tick sound
	sf::Sound m_bombTickSound;
	// init
	void init();
	// explode
	void explode();
	// try add blowing up bomb to cell
	void tryAddBub(const sf::Vector2f& relPos);
};



