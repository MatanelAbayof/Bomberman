//---- include section ------
#include "WinScreen.h"
#include "Resources.h"

// init
const sf::Color WinScreen::BACK_BT_BACK_COLOR = sf::Color(210, 166, 3);
const sf::Color WinScreen::BACK_BT_ENTER_BACK_COLOR = sf::Color(197, 156, 4);

WinScreen::WinScreen(sf::RenderWindow& window, int numOfScore)
	: RelativeLayout(window), m_mainMessage(window), m_scoreMessage(window), m_backBt(window)
{
	init();
	setNumOfScore(numOfScore);
}

void WinScreen::setNumOfScore(int numOfScore)
{
	m_scoreMessage.setText("Your score is " + std::to_string(numOfScore));
}

TextView& WinScreen::getBackButton()
{
	return m_backBt;
}

string WinScreen::toString() const
{
	return "WinScreen: " + RelativeLayout::toString();
}

void WinScreen::init()
{
	getBackground().setTexture(Resources::Images::WinBackground);

	// init main message
	m_mainMessage.setTextColor(sf::Color(140, 179, 69));
	m_mainMessage.setTextSize(70);
	m_mainMessage.setText("You win!");

	// init score message text
	m_scoreMessage.setTextColor(sf::Color(74, 106, 255));
	m_scoreMessage.setTextSize(60);

	// init back to MainScreen button
	m_backBt.getBackground().setColor(BACK_BT_BACK_COLOR);
	m_backBt.setBorder(Border(sf::Color(133, 104, 0), 4));
	m_backBt.setTextColor(sf::Color::White);
	m_backBt.setTextSize(50);
	m_backBt.setFont(Resources::Fonts::ARBD);
	m_backBt.setText("Back to main");

	// listen to click, enter and leave events
	m_backBt.addClickListener(View::ClickHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtClick);
		this->m_btSound.play();
	}));
	m_backBt.addEnterListener(View::EnterHandler::Listener([this](View& view) {
		this->m_btSound.setBuffer(Resources::Sounds::BtHover);
		this->m_btSound.play();
		view.getBackground().setColor(WinScreen::BACK_BT_ENTER_BACK_COLOR);
	}));
	m_backBt.addLeaveListener(View::LeaveHandler::Listener([this](View& view) {
		view.getBackground().setColor(WinScreen::BACK_BT_BACK_COLOR);
	}));

	// add views
	addView(m_mainMessage, sf::FloatRect(1.f/9.f, 0.05f, 0.8f, 0.1f));
	addView(m_scoreMessage, sf::FloatRect(1.f/9.f, 0.2f, 0.8f, 0.1f));
	addView(m_backBt, sf::FloatRect(1.f/3.f, 0.7f, 1.f/3.f, 0.15f));
}
