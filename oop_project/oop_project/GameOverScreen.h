#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "RelativeLayout.h"
#include "TextView.h"
#include <string>

//---- using section --------
using std::string;

/*
 * GameOverScreen class
 */
class GameOverScreen :
	public RelativeLayout
{
public:
	// losing background color
	static const sf::Color LOSING_BT_BACK_COLOR;
	// back to main background color
	static const sf::Color TO_MAIN_BT_BACK_COLOR;
	static const sf::Color TO_MAIN_BT_ENTER_BACK_COLOR;
	// constructor
	GameOverScreen(sf::RenderWindow& window);
	// get losing button
	TextView& getlosingButton();
	// get start button
	TextView& getBackToMainButton();
	// convert to string
	virtual string toString() const override;
private:
	// buttons
	TextView m_losing, m_backToMain;
	// buttons sound
	sf::Sound m_btSound;
	// init buttons
	void init();
};

