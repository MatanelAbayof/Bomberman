#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "RelativeLayout.h"
#include "TextView.h"
#include <string>

//---- using section --------
using std::string;

/*
 * WinScreen class
 */
class WinScreen :
	public RelativeLayout
{
public:
	// back to MainScreen background color
	static const sf::Color BACK_BT_BACK_COLOR;
	static const sf::Color BACK_BT_ENTER_BACK_COLOR;
	// constructor
	WinScreen(sf::RenderWindow& window, int numOfScore = 0);
	// set num of scores
	void setNumOfScore(int numOfScore);
	// get back to MainScreen button
	TextView& getBackButton();
	// convert to string
	virtual string toString() const override;
private:
	// buttons
	TextView m_mainMessage, m_scoreMessage, m_backBt;
	// buttons sound
	sf::Sound m_btSound;
	// init buttons
	void init();
};

