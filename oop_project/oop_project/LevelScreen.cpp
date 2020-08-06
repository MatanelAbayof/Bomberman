//---- include section ------
#include "LevelScreen.h"

LevelScreen::LevelScreen(sf::RenderWindow & window)
	: VerticalLayout(window), m_gameMenu(window), m_levelMap(window)
{
	setUseBombs(false);
	setUseTimeLeft(false);
	initComponent();
}

GameMenu& LevelScreen::getGameMenu()
{
	return m_gameMenu;
}

LevelMap& LevelScreen::getLevelMap()
{
	return m_levelMap;
}

void LevelScreen::setUseTimeLeft(bool isUsingTimeLeft)
{
	m_useTimeLeft = isUsingTimeLeft;
	if (m_useTimeLeft) {
		m_gameMenu.getTimeLeftView().show();
	}
	else
		m_gameMenu.getTimeLeftView().hide();
}

void LevelScreen::setUseBombs(bool isUsingBombs)
{
	m_useBombs = isUsingBombs;
	if (m_useBombs) {
		m_gameMenu.getBombsView().show();
	}
	else
		m_gameMenu.getBombsView().hide();
}

bool LevelScreen::isUseTimeLeft() const
{
	return m_useTimeLeft;
}

bool LevelScreen::isUseBombs() const
{
	return m_useBombs;
}

void LevelScreen::clear()
{
	m_useBombs = false;
	m_useTimeLeft = false;
	m_gameMenu.clear();
	m_levelMap.clear();
}

string LevelScreen::toString() const
{
	return "LevelScreen: " + VerticalLayout::toString();
}

void LevelScreen::initComponent()
{
	setBorder(Border(sf::Color::Black, 2));
	addView(m_gameMenu, 0.1f);
	addView(m_levelMap, 0.9f);
}
