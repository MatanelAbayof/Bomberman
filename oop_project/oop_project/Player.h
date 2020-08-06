#pragma once
//---- include section ------
#include "DynamicCharacter.h"
#include <functional>
#include <string>

//---- using section --------
using std::string;

/*
 * Player class
 */
class Player :
	public DynamicCharacter
{
public:
	// player shape
	static const char PLAYER_SHAPE = '/';
	// robot draw priority
	static const int PLAYER_DRAW_PRIORITY = 20;
	// constructors
	Player(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0),
		   const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	Player(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0),
		   const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// set direction
	virtual void setDirection(Direction direction);
	// play
	virtual void play();
	// handle key pressed
	void handleKeyPressed(const sf::Keyboard::Key& keyCode);
	// handle key released
	void handleKeyReleased(const sf::Keyboard::Key& keyCode);
	// convert to string
	virtual string toString() const override;
	// set on end level event
	void setOnEndLevelListener(std::function<void()> onEndLevel);
	// set on die listener event
	void setOnDieListener(std::function<void()> onDieListener);
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
	// die & end level events
	std::function<void()> m_dieHandler, m_endLevelHandler;
	// init player
	void init();
	// create bomb
	void createBomb();
	// call end level event
	void callEndLevelEvent();
	// call die event
	void callDieEvent();
	// animation frequency
	static const int PLAYER_ANIM_FREQUENCY = 60;
	// gifts
	static const int BOMB_GIFT = 5;
	static const int SCORE_GIFT = 50;
	static const int TIME_GIFT = 20000; // in milliseconds
	static const float APPEND_SPEED_GIFT;// speed to append when speed gift are picked
};

