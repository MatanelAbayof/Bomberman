#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include "RelativeLayout.h"
#include "TextView.h"
#include <string>

//---- using section --------
using std::string;

/*
 * MainScreen class
 */
class MainScreen :
	public RelativeLayout
{
public:
	// start background color
	static const sf::Color START_BT_BACK_COLOR;
	static const sf::Color START_BT_ENTER_BACK_COLOR;
	// end background color
	static const sf::Color END_BT_BACK_COLOR;
	static const sf::Color END_BT_ENTER_BACK_COLOR;
	// constructor
	MainScreen(sf::RenderWindow& window);
	// get start button
	TextView& getStartButton();
	// get end button
	TextView& getExitButton();
	// convert to string
	virtual string toString() const override;
private:
	// buttons
	TextView m_start, m_exit;
	// buttons sound
	sf::Sound m_btSound;
	// init buttons
	void init();
};