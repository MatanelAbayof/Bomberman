#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "StaticCharacter.h"
#include "StopWatch.h"

/*
 * Gift class
 */
class Gift :
	public StaticCharacter
{
public:
	// gift shape
	static const char GIFT_SHAPE = '+';
	// gift under rock shape
	static const char GIFT_UNDER_ROCK_SHAPE = '&';
	// num of gift types
	static const int NUM_OF_GIFT_TYPE = 5;
	// types of gift (numbers in binary base)
	enum GiftType { BOMB = 0b00001, LIFE = 0b00010, SCORE = 0b00100, TIME = 0b01000, SPEED = 0b10000 };
	// gift state
	enum GiftState { OPEN, CLOSE };
	// robot draw priority
	static const int GIFT_DRAW_PRIORITY = 7;
	// constructors
	Gift(sf::RenderWindow& window, LevelScreen& levelScreen, 
		const sf::Vector2f& relPos = sf::Vector2f(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0), 
		GiftType giftType = GiftType::BOMB);
	Gift(sf::RenderWindow& window, LevelScreen& levelScreen,
		 const Cell& cell = Cell(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0), 
		 GiftType giftType = GiftType::BOMB);
	// set gift state
	void setGiftState(GiftState giftState);
	// get gift state
	GiftState getGiftState() const;
	// get gift type
	GiftType getGiftType() const;
	// set gift type
	void setGiftType(GiftType giftType);
	// get random gift type. allowed gifts with OR logic gate (must be least with one type!)
	static GiftType randGiftType(short allowedGifts);
	// draw
	virtual void draw();
	// convert to string
	virtual string toString() const override;
	// make unique ptr
	virtual std::unique_ptr<Character> clone();
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
	// gift open sound
	sf::Sound m_giftOpenSound;
	// gift type
	GiftType m_giftType;
	// init
	void init();
	// convert gift type to string
	static string giftTypeToStr(GiftType giftType);
	// stoper start when picked until vanishing
	StopWatch m_pickedStoper;
	// gift state
	GiftState m_giftState;
};

