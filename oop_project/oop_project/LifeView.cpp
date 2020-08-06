#include "LifeView.h"
#include <memory>

LifeView::LifeView(sf::RenderWindow& window, int numOfLife)
	: HorizontalLayout(window)
{
	initComponents();

	setNumOfLife(numOfLife);
}

void LifeView::setNumOfLife(int numOfLife)
{
	if (!isLegalLife(numOfLife))
		throw string("No have legal life=" + std::to_string(numOfLife));

	// remove all lifes
	removeAllViews();
	m_lifes.clear();

	// set new life
	m_numOfLife = numOfLife;
	for (int i = 0; i < m_numOfLife; i++)
		addOneLifeView();
}

int LifeView::getNumOfLife() const
{
	return m_numOfLife;
}

bool LifeView::hasNoLife() const
{
	return (m_numOfLife == 0);
}

LifeView& LifeView::operator++(int)
{
	m_numOfLife++;
	addOneLifeView();

	return *this;
}

LifeView& LifeView::operator--(int)
{
	int newLife = m_numOfLife - 1;

	if (!isLegalLife(newLife))
		throw string("No have legal life=" + std::to_string(newLife));

	m_numOfLife = newLife;

	// remove last life
	removeView(newLife);
	m_lifes.erase(m_lifes.begin() + newLife);

	arrangeChildrens();

	return *this;
}

string LifeView::toString() const
{
	return "LifeView: numOfLife=" + std::to_string(m_numOfLife);
}

bool LifeView::isLegalLife(int numOfLife) const
{
	return numOfLife >= 0;
}

void LifeView::addOneLifeView()
{
	// create new life image
	m_lifes.push_back(std::make_unique<ImageView>(ImageView(getWindow(), ImageTexture(Resources::Images::Life))));
	// add life image to HorizontalLayout
	addView(*m_lifes[m_lifes.size() - 1]);
}

void LifeView::initComponents()
{
	// set my border
	setBorder(Border(sf::Color::Black, 1));
}
