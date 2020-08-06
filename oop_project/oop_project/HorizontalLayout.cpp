//---- include section ------
#include "HorizontalLayout.h"

HorizontalLayout::HorizontalLayout(sf::RenderWindow& window)
				: ViewGroup(window)
{ }

void HorizontalLayout::addView(View& view)
{
	float relativeWidth = (float)1 / (getNumOfViews() + 1);
	addView(view, relativeWidth);
	arrangeChildrens();
}

void HorizontalLayout::addView(View& view, float relativeWidth)
{
	ViewGroup::addView(view);
	if (!checkRelativeWidth(relativeWidth))
		throw string("Can't set relative width " + std::to_string(relativeWidth));
	m_relativeWidths.push_back(relativeWidth);
	updateComponents();
}

void HorizontalLayout::removeView(int index)
{
	ViewGroup::removeView(index);
	m_relativeWidths.erase(m_relativeWidths.begin() + index);
	updateComponents();
}

void HorizontalLayout::arrangeChildrens()
{
	if (getNumOfViews() > 0) {
		float relativeWidth = (float)1 / getNumOfViews();
		for (size_t i = 0; i < m_relativeWidths.size(); i++)
			m_relativeWidths[i] = relativeWidth;
		updateComponents();
	}
}

string HorizontalLayout::toString() const
{
	return "HorizontalLayout: view=" + ViewGroup::toString();
}

void HorizontalLayout::updateComponents()
{
	ViewGroup::updateComponents();

	if (isNoSet())
		return;

	if (getNumOfViews() > 0) {
		int childX = 0;
		int childHeight = getHeight();

		for (int i = 0; i < getNumOfViews(); i++) {
			int childWidth = (int)(m_relativeWidths[i] * getWidth());
			sf::Vector2f childPosition(getPosition().x + childX, getPosition().y);
			View &view = getView(i);
			view.setBound(childPosition, childWidth, childHeight);

			childX += childWidth;
		}
	}	
}

bool HorizontalLayout::checkRelativeWidth(float relativeWidth) const
{
	return ((relativeWidth >= 0) && (relativeWidth <= 1));
}
