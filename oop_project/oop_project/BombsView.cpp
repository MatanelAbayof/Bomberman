//---- include section ------
#include "BombsView.h"
#include "Resources.h"

BombsView::BombsView(sf::RenderWindow& window, int numOfBombs)
	:ImageButton(window)
{
	initComponents();

	setNumOfBombs(numOfBombs);
}

void BombsView::setNumOfBombs(int numOfBombs)
{
	if (!isLegalBombs(numOfBombs))
		throw string("Number of bombs must be bigger or equals to zero (=" + std::to_string(numOfBombs) + ")");
	m_numOfBombs = numOfBombs;
	// update text
	setText(std::to_string(numOfBombs));
}

int BombsView::getNumOfBombs() const
{
	return m_numOfBombs;
}

bool BombsView::hasBombs() const
{
	return (m_numOfBombs > 0);
}

BombsView & BombsView::operator++(int)
{
	setNumOfBombs(m_numOfBombs + 1);
	return *this;
}

BombsView& BombsView::operator--(int)
{
	setNumOfBombs(m_numOfBombs - 1);
	return *this;
}

BombsView& BombsView::operator+=(int numOfBombs)
{
	setNumOfBombs(m_numOfBombs + numOfBombs);
	return *this;
}

BombsView& BombsView::operator-=(int numOfBombs)
{
	setNumOfBombs(m_numOfBombs - numOfBombs);
	return *this;
}

string BombsView::toString() const
{
	return "BombsView: numOfBombs=" + std::to_string(m_numOfBombs);
}

bool BombsView::isLegalBombs(int numOfBombs) const
{
	return (numOfBombs >= 0);
}

void BombsView::initComponents()
{
	setTextColor(sf::Color::Black);
	setImage(Resources::Images::Bomb);
	setTextHAligment(TextView::TextHAlignment::LEFT);
}
