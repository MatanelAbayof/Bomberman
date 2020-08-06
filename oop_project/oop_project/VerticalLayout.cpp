//---- include section ------
#include "VerticalLayout.h"

VerticalLayout::VerticalLayout(sf::RenderWindow& window)
	: ViewGroup(window)
{ }

string VerticalLayout::toString() const
{
	return "VerticalLayout: view=" + ViewGroup::toString();
}

void VerticalLayout::addView(View &view)
{
	float relativeHeight = (float) 1 / (getNumOfViews() + 1);
	addView(view, relativeHeight);
	arrangeChildrens();
}

void VerticalLayout::addView(View &view, float relativeHeight)
{
	ViewGroup::addView(view);
	if (!checkRelativeHeight(relativeHeight))
		throw string("Can't set relative height " + std::to_string(relativeHeight));
	m_relativeHeights.push_back(relativeHeight);
	updateComponents();
}

void VerticalLayout::removeView(int index)
{
	ViewGroup::removeView(index);
	m_relativeHeights.erase(m_relativeHeights.begin() + index);
	updateComponents();
}

void VerticalLayout::arrangeChildrens()
{
	if (getNumOfViews() > 0) {
		float relativeHeight = (float) 1 / getNumOfViews();
		for (size_t i = 0; i < m_relativeHeights.size(); i++)
			m_relativeHeights[i] = relativeHeight;
		updateComponents();
	}	
}

float VerticalLayout::getChildRelativeHeight(int index) const
{
	if (!haveViewAt(index))
		throw string("No found view at " + std::to_string(index) + " index");
	return m_relativeHeights[index];
}

void VerticalLayout::updateComponents()
{
	ViewGroup::updateComponents();

	if (isNoSet())
		return;

	if (getNumOfViews() > 0) {
		int childWidth = getWidth();
		int childY = 0;
		for (int i = 0; i < getNumOfViews(); i++) {
			int childHeight = (int) (m_relativeHeights[i] * getHeight());
			sf::Vector2f childPosition(getPosition().x, getPosition().y + childY);
			View &view = getView(i);
			view.setBound(childPosition, childWidth, childHeight);

			childY += childHeight;
		}
	}
}

bool VerticalLayout::checkRelativeHeight(float relativeHeight) const
{
	return ((relativeHeight >= 0) && (relativeHeight <= 1));
}
