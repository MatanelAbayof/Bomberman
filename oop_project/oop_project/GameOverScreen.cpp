#include "GameOverScreen.h"
#include "Resources.h"


// init
const sf::Color GameOverScreen::LOSING_BT_BACK_COLOR = sf::Color::Transparent;
const sf::Color GameOverScreen::TO_MAIN_BT_BACK_COLOR = sf::Color(204, 204, 0);
const sf::Color GameOverScreen::TO_MAIN_BT_ENTER_BACK_COLOR = sf::Color(153, 204, 0);

GameOverScreen::GameOverScreen(sf::RenderWindow & window)
	:RelativeLayout(window), m_backToMain(window), m_losing(window)
{
	init();
}

TextView & GameOverScreen::getlosingButton()
{
	return m_losing;
}

TextView & GameOverScreen::getBackToMainButton()
{
	return m_backToMain;
}

string GameOverScreen::toString() const
{
	return "GameOverScreen: " + RelativeLayout::toString();
}

void GameOverScreen::init()
{
	getBackground().setTexture(Resources::Images::GameOverBackground);

	// init losing button
	m_losing.getBackground().setColor(LOSING_BT_BACK_COLOR);
	m_losing.setTextColor(sf::Color(204, 0, 0));
	m_losing.setTextSize(90);
	m_losing.setFont(Resources::Fonts::ARBD);
	m_losing.setText("You lose asshole!");

	// init back to main screen button
	m_backToMain.getBackground().setColor(TO_MAIN_BT_BACK_COLOR);
	m_backToMain.setBorder(Border(sf::Color(109, 109, 109), 4));
	m_backToMain.setTextColor(sf::Color::White);
	m_backToMain.setTextSize(50);
	m_backToMain.setFont(Resources::Fonts::ARBD);
	m_backToMain.setText("Back To Main");

	// listen to click, enter and hover events
	m_backToMain.addClickListener(View::ClickHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtClick);
		this->m_btSound.play();
	}));
	m_backToMain.addEnterListener(View::EnterHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtHover);
		this->m_btSound.play();
		view.getBackground().setColor(GameOverScreen::TO_MAIN_BT_ENTER_BACK_COLOR);
	}));
	m_backToMain.addLeaveListener(View::LeaveHandler::Listener([this](View& view) {
		view.getBackground().setColor(GameOverScreen::TO_MAIN_BT_BACK_COLOR);
	}));

	addView(m_losing, sf::FloatRect(1.f / 4.f, 0.1f, 1.f / 2.f, 0.2f));
	addView(m_backToMain, sf::FloatRect(1.f / 3.f, 0.65f, 1.f / 3.f, 0.15f));
}
