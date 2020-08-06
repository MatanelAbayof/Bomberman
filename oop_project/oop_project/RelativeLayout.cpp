//---- include section ------
#include "RelativeLayout.h"

RelativeLayout::RelativeLayout(sf::RenderWindow& window)
	: ViewGroup(window)
{ }

void RelativeLayout::addView(View& view, const sf::FloatRect& relativeBounds)
{
	if (!checkRelativeBounds(relativeBounds))
		throw string("Relative bounds must be numbers between 0-1");
	
	ViewGroup::addView(view);
	m_relativeBounds.push_back(relativeBounds);
	updateComponents();
}

void RelativeLayout::removeView(int index)
{
	ViewGroup::removeView(index);
	m_relativeBounds.erase(m_relativeBounds.begin() + index);
	updateComponents();
}

string RelativeLayout::toString() const
{
	return "RelativeLayout: " + ViewGroup::toString();
}

void RelativeLayout::updateComponents()
{
	ViewGroup::updateComponents();

	if (isNoSet())
		return;

	if (getNumOfViews() > 0) {
		for (int i = 0; i < getNumOfViews(); i++) {
			sf::FloatRect& relativeCBounds = m_relativeBounds[i];
			sf::FloatRect childBounds(getPosition().x + getWidth()*relativeCBounds.left, getPosition().y + getHeight()*relativeCBounds.top,
				                  getWidth()*relativeCBounds.width, getHeight()*relativeCBounds.height);
			View &childView = getView(i);
			childView.setBound(childBounds);
		}
	}
}

bool RelativeLayout::checkRelativeBounds(const sf::FloatRect& relativeBounds) const
{
	return checkBoundNumOK(relativeBounds.left) && checkBoundNumOK(relativeBounds.top) &&
		   checkBoundNumOK(relativeBounds.width) && checkBoundNumOK(relativeBounds.height);
}

bool RelativeLayout::checkBoundNumOK(float num) const
{
	return (num >= 0) && (num <= 1);
}
