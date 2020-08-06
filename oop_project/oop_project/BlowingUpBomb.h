#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "StaticCharacter.h"
#include "StopWatch.h"

/*
 * BlowingUpBomb class
 */
class BlowingUpBomb :
	public StaticCharacter
{
public:
	// blowing up bomb draw priority
	static const int BUB_DRAW_PRIORITY = 25;
	// constructors
	BlowingUpBomb(sf::RenderWindow& window, LevelScreen& levelScreen,
		const sf::Vector2f& relPos = sf::Vector2f(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	BlowingUpBomb(sf::RenderWindow& window, LevelScreen& levelScreen,
		const Cell& cell = Cell(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// copy constructor
	BlowingUpBomb(BlowingUpBomb& anotherBub);
	// draw
	virtual void draw();
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
	// stop watch (time to destroy)
	StopWatch m_stoper;
	// flag for first drawing time
	bool m_firstDraw;
	// sound of explosion
	sf::Sound m_bubSound;
};

