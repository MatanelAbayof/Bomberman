//---- include section ------
#include "ScoreView.h"
#include "Resources.h"


ScoreView::ScoreView(sf::RenderWindow& window, int numOfScore)
	: ImageButton(window)
{
	initComponents();

	setNumOfScore(numOfScore);
}

void ScoreView::setNumOfScore(int numOfScore)
{
	if (!isLegalScore(numOfScore))
		throw string("Number of score must be bigger or equals to zero (=" + std::to_string(numOfScore) + ")");
	m_numOfScore = numOfScore;
	// update text
	setText(std::to_string(numOfScore));
}

int ScoreView::getNumOfScore() const
{
	return m_numOfScore;
}

ScoreView& ScoreView::operator++(int)
{
	setNumOfScore(m_numOfScore + 1);
	return *this;
}

ScoreView& ScoreView::operator--(int)
{
	setNumOfScore(m_numOfScore - 1);
	return *this;
}

ScoreView& ScoreView::operator+=(int numOfBombs)
{
	setNumOfScore(m_numOfScore + numOfBombs);
	return *this;
}

ScoreView& ScoreView::operator-=(int numOfBombs)
{
	setNumOfScore(m_numOfScore - numOfBombs);
	return *this;
}

string ScoreView::toString() const
{
	return "ScoreView: numOfScore=" + std::to_string(m_numOfScore);
}

bool ScoreView::isLegalScore(int numOfScore) const
{
	return (numOfScore >= 0);
}

void ScoreView::initComponents()
{
	setTextColor(sf::Color(255, 178, 45));
	setImage(Resources::Images::Coin);
	setTextHAligment(TextView::TextHAlignment::LEFT);
}
