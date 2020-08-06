#pragma once
//---- include section ------
#include <string>
#include "ViewGroup.h"

//---- using section --------
using std::string;

/*
 * HorizontalLayout class
 */
class HorizontalLayout :
	public ViewGroup
{
public:
	// constructor
	HorizontalLayout(sf::RenderWindow& window);
	// add view with default width
	virtual void addView(View& view) override;
	// add view with custom width
	virtual void addView(View& view, float relativeWidth);
	// remove view
	virtual void removeView(int index) override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
	// arrange all childrens with same widths
	void arrangeChildrens();
private:
	// childrens relative heights
	vector<float> m_relativeWidths;
	// check relative height
	bool checkRelativeWidth(float relativeWidth) const;	
};

