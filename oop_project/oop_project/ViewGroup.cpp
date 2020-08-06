//---- include section ------
#include "ViewGroup.h"

ViewGroup::ViewGroup(sf::RenderWindow& window)
	: View(window)
{ }

void ViewGroup::addView(View &view)
{
	// add self as parent view 
	view.setParent(*this);
	// add view
	m_views.push_back(&view);	
}

void ViewGroup::removeAllViews()
{
	m_views.clear();
}

View &ViewGroup::getView(int index) const
{
	if (!haveViewAt(index))
		throw string("No found view at " + std::to_string(index) + " index");
	return *m_views[index];
}

void ViewGroup::removeView(int index)
{
	if (!haveViewAt(index))
		throw string("No found view at " + std::to_string(index) + " index");
	m_views.erase(m_views.begin() + index);
}

int ViewGroup::getNumOfViews() const
{
	return static_cast<int>(m_views.size());
}

void ViewGroup::draw()
{
	View::draw();

	if (isShow()) {
		// draw children
		for (View *view : m_views)
			view->draw();
	}
}

string ViewGroup::toString() const
{
	string str = "ViewGroup: view=" + View::toString() + ", childs={\n";
	for (View *view : m_views)
		str += "v=" + view->toString() + "\n";
	str += "}";
	return str;
}

void ViewGroup::handleClickEvent(int mouseX, int mouseY)
{
	View::handleClickEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		for (View *view : m_views)
			view->handleClickEvent(mouseX, mouseY);
	}
}

void ViewGroup::handleEnterEvent(int mouseX, int mouseY)
{
	View::handleEnterEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		for (View *view : m_views)
			view->handleEnterEvent(mouseX, mouseY);
	}
}

void ViewGroup::handleLeaveEvent(int mouseX, int mouseY)
{
	View::handleLeaveEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		for (View *view : m_views)
			view->handleLeaveEvent(mouseX, mouseY);
	}
}

bool ViewGroup::haveViewAt(int index) const
{
	return (index >= 0) && (index < getNumOfViews());
}
