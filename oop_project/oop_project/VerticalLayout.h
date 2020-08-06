#pragma once
//---- include section ------
#include <string>
#include "ViewGroup.h"

//---- using section --------
using std::string;

/*
 * VerticalLayout class
 */
class VerticalLayout :
	public ViewGroup
{
public:
	// constructor
	VerticalLayout(sf::RenderWindow& window);
	// add view with default height
	virtual void addView(View& view) override;
	// add view
	virtual void addView(View& view, float relativeHeight);
	// remove view
	virtual void removeView(int index) override;
	// get relative height of child
	float getChildRelativeHeight(int index) const;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
	// arrange childrens with same heights
	void arrangeChildrens();
private:
	// my view relative heights
	vector<float> m_relativeHeights;
	// check relative height
	bool checkRelativeHeight(float relativeHeight) const;
};