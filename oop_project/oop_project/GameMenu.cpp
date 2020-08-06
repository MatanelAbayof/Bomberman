//---- include section ------
#include "GameMenu.h"
#include "TextView.h"

GameMenu::GameMenu(sf::RenderWindow& window)
	: HorizontalLayout(window), m_scoreView(window), m_bombsView(window), m_lifeView(window),
	  m_numLevelView(window), m_restartButton(window), m_timeLeftView(window)
{
	initComponents();
}

void GameMenu::initComponents()
{
	// set my border
	setBorder(Border(sf::Color::Black, 1));
	// set my background
	getBackground().setColor(sf::Color(240, 255, 239));
	
	setRestartButton();

	init(m_scoreView);
	init(m_bombsView);
	initLifeView(m_lifeView);
	init(m_timeLeftView);
	initTextView(m_numLevelView);
	initTextView(m_restartButton);
}

void GameMenu::init(ImageButton &ImageButton)
{
	addView(ImageButton);
}

void GameMenu::initTextView(TextView &textView)
{
	textView.setBorder(Border(sf::Color::Black, 1));
	addView(textView);
}

void GameMenu::initLifeView(LifeView & liveView)
{
	m_lifeView.setNumOfLife(3);
	addView(m_lifeView);
}

ScoreView& GameMenu::getScoreView()
{
	return m_scoreView;
}

LifeView& GameMenu::getLifeview()
{
	return m_lifeView;
}

BombsView& GameMenu::getBombsView()
{
	return m_bombsView;
}

TimeLeftView& GameMenu::getTimeLeftView()
{
	return m_timeLeftView;
}

NumLevelView& GameMenu::getNumLevelView()
{
	return m_numLevelView;
}

TextView& GameMenu::getRestartButton()
{
	return m_restartButton;
}

void GameMenu::setRestartButton()
{
	m_restartButton.setText("Restart");
	m_restartButton.setTextColor(sf::Color::Black);
	// set background color when enter or leave to button
	sf::Color enterBColor = sf::Color(192, 2, 2), BColor = sf::Color::Red;
	m_restartButton.getBackground().setColor(BColor);
	m_restartButton.addEnterListener(View::EnterHandler::Listener([enterBColor](View& view) {
		view.getBackground().setColor(enterBColor);
	}));
	m_restartButton.addLeaveListener(View::LeaveHandler::Listener([BColor](View& view) {
		view.getBackground().setColor(BColor);
	}));
}

void GameMenu::clear()
{
	m_bombsView.setNumOfBombs(0);
	m_bombsView.hide();
	m_timeLeftView.stop();
}

string GameMenu::toString() const
{
	return "GameMenu: " + HorizontalLayout::toString();
}