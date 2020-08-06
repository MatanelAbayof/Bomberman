#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "DynamicCharacter.h"
#include "AnimationView.h"
#include "StopWatch.h"
#include <string>

//---- using section --------
using std::string;

/*
 * Guard class
 */
class Guard :
	public DynamicCharacter
{
public:
	// guard health state
	enum HealthState {
		LIVE, READY_TO_DIE
	};
	// guard type
	enum GuardType { STUPID = 0, SMART = 1 };
	// guard shape
	static const char GUARD_SHAPE = '!';
	// guard draw priority
	static const int GUARD_DRAW_PRIORITY = 18;
	// set direction
	virtual void setDirection(Direction direction) override;
	// convert to string
	virtual string toString() const override;
	// get health state
	HealthState getHealthState() const;
	// rand guard type
	static GuardType randGuardType();
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
	// draw
	virtual void draw() override;
protected:
	// get random direction (4 directions)
	DynamicCharacter::Direction getRandomDirect() const;
	// get horizontal random direction (left or right)
	DynamicCharacter::Direction getHRandomDirect() const;
	// get vertical random direction (up or down)
	DynamicCharacter::Direction getVRandomDirect() const;
	// constructors
	Guard(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0), 
		  const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	Guard(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0), 
		  const sf::Vector2f& relSize = sf::Vector2f(0, 0));
private:
	// die stop watch
	StopWatch m_dieStoper;
	// die sound
	sf::Sound m_dieSound;
	// helafh state
	HealthState m_healfh;
	// init guard
	void init();
	// animation frequency
	static const int GUARD_ANIM_FREQUENCY = 30;
	// score
	static const int SCORE_FOR_KILL_GUARD = 5;
	// ready to die
	void readyToDie();
};

