//---- include section ------
#include "MainScreen.h"
#include "Resources.h"

// init
const sf::Color MainScreen::START_BT_BACK_COLOR = sf::Color::Blue;
const sf::Color MainScreen::START_BT_ENTER_BACK_COLOR = sf::Color(0, 51, 153);
const sf::Color MainScreen::END_BT_BACK_COLOR = sf::Color::Red;
const sf::Color MainScreen::END_BT_ENTER_BACK_COLOR = sf::Color(204, 0, 0);

MainScreen::MainScreen(sf::RenderWindow& window)
	: RelativeLayout(window), m_start(window), m_exit(window)
{
	init();
}

TextView& MainScreen::getStartButton() 
{
	return m_start;
}

TextView& MainScreen::getExitButton() 
{
	return m_exit;
}

string MainScreen::toString() const
{
	return "MainScreen: " + RelativeLayout::toString();
}

void MainScreen::init()
{
	getBackground().setTexture(Resources::Images::BombermanBackground);

	// init start game button
	m_start.getBackground().setColor(START_BT_BACK_COLOR);
	m_start.setBorder(Border(sf::Color(109, 109, 109), 4));
	m_start.setTextColor(sf::Color::White);
	m_start.setTextSize(50);
	m_start.setFont(Resources::Fonts::ARBD);
	m_start.setText("Start Game");

	// init end game button
	m_exit.getBackground().setColor(END_BT_BACK_COLOR);
	m_exit.setBorder(Border(sf::Color(109, 109, 109), 4));
	m_exit.setTextColor(sf::Color::White);
	m_exit.setTextSize(50);
	m_exit.setFont(Resources::Fonts::ARBD);
	m_exit.setText("End Game");

	// listen to click, enter and hover events
	m_start.addClickListener(View::ClickHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtClick);
		this->m_btSound.play();
	}));
	m_start.addEnterListener(View::EnterHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtHover);
		this->m_btSound.play();
		view.getBackground().setColor(MainScreen::START_BT_ENTER_BACK_COLOR);
	}));
	m_start.addLeaveListener(View::LeaveHandler::Listener([this](View& view) {
		view.getBackground().setColor(MainScreen::START_BT_BACK_COLOR);
	}));
	m_exit.addClickListener(View::ClickHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtClick);
		this->m_btSound.play();
	}));
	m_exit.addEnterListener(View::EnterHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtHover);
		this->m_btSound.play();
		view.getBackground().setColor(MainScreen::END_BT_ENTER_BACK_COLOR);
	}));
	m_exit.addLeaveListener(View::LeaveHandler::Listener([](View& view) {
		view.getBackground().setColor(MainScreen::END_BT_BACK_COLOR);
	}));

	addView(m_start, sf::FloatRect(1.f/3.f, 0.35f, 1.f / 3.f, 0.15f));
	addView(m_exit, sf::FloatRect(1.f / 3.f, 0.55f, 1.f / 3.f, 0.15f));
}
