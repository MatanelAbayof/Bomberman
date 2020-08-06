#pragma once
//---- include section ------
#include <string>
#include <vector>
#include "ViewGroup.h"

//---- using section --------
using std::string;
using std::vector;

/*
 * RelativeLayout class
 */
class RelativeLayout :
	public ViewGroup
{
public:
	// constructor
	RelativeLayout(sf::RenderWindow& window);
	// add view
	virtual void addView(View& view, const sf::FloatRect& relativeBounds);
	// remove view
	virtual void removeView(int index) override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
private:
	// relative bounds of children
	vector<sf::FloatRect> m_relativeBounds;
	// check relative bounds
	bool checkRelativeBounds(const sf::FloatRect& relativeBounds) const;
	// check if number between 0-1
	bool checkBoundNumOK(float num) const;
};

