//---- include section ------
#include "NumLevelView.h"

NumLevelView::NumLevelView(sf::RenderWindow& window, int numOfLevel)
	: TextView(window)
{
	setNumOfLevel(numOfLevel);
	setTextColor(sf::Color::Black);
}

void NumLevelView::setNumOfLevel(int numOfLevel)
{
	if (!isLegalLevel(numOfLevel))
		throw string("No legal num level " + std::to_string(numOfLevel));

	m_numOfLevel = numOfLevel;

	updateLevelText();
}

int NumLevelView::getNumOfLevel() const
{
	return m_numOfLevel;
}

NumLevelView & NumLevelView::operator++(int)
{
	setNumOfLevel(m_numOfLevel + 1);
	return *this;
}

NumLevelView& NumLevelView::operator--(int)
{
	setNumOfLevel(m_numOfLevel - 1);
	return *this;
}

string NumLevelView::toString() const
{
	return "NumLevelView: numOfLevel=" + std::to_string(m_numOfLevel);
}

bool NumLevelView::isLegalLevel(int numOfLevel) const
{
	return (numOfLevel >= 0);
}

void NumLevelView::updateLevelText()
{
	setText("Level: " + std::to_string(m_numOfLevel + 1));
}

