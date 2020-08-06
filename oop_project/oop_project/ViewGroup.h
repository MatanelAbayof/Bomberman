#pragma once
//---- include section ------
#include <string>
#include <vector>
#include "View.h"

//---- using section --------
using std::string;
using std::vector;

/*
 * ViewGroup abstract class
 */
class ViewGroup :
	public View
{
public:
	// get view by index
	virtual View& getView(int index) const;
	// get number of views
	virtual int getNumOfViews() const;
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	ViewGroup(sf::RenderWindow& window);
	// handle click event
	virtual void handleClickEvent(int mouseX, int mouseY) override;
	// handle enter event
	virtual void handleEnterEvent(int mouseX, int mouseY) override;
	// handle leave event
	virtual void handleLeaveEvent(int mouseX, int mouseY) override;
	// check if have view in index
	bool haveViewAt(int index) const;
	// remove view
	virtual void removeView(int index);
	// add view
	virtual void addView(View& view);
	// remove all views
	virtual void removeAllViews();
private:
	// my childrens
	vector<View*> m_views;
};

