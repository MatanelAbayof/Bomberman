#pragma once
//---- include section ------
#include "VerticalLayout.h"
#include "GameMenu.h"
#include "LevelMap.h"

/*
 * LevelScreen class
 */
class LevelScreen :
	public VerticalLayout
{
public:
	LevelScreen(sf::RenderWindow& window);
	// get game menu
	GameMenu& getGameMenu();
	// get level map
	LevelMap& getLevelMap();
	// set use time left
	void setUseTimeLeft(bool isUsingTimeLeft);
	// set useBombs
	void setUseBombs(bool isUsingBombs);
	//get useTimeLeft
	bool isUseTimeLeft() const;
	//get useBombs
	bool isUseBombs() const;
	// clear
	void clear();
	//convert to string
	virtual string toString() const override;
private:
	// game menu
	GameMenu m_gameMenu;
	// level map
	LevelMap m_levelMap;
	// if use with time and bombs
	bool m_useTimeLeft, m_useBombs;
	// init component
	void initComponent();	
};

