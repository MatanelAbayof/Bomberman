#pragma once
//---- include section ------
#include "TextView.h"

/*
 * NumLevelView class
 */
class NumLevelView :
	public TextView
{
public:
	// constructor
	NumLevelView(sf::RenderWindow& window, int numOfLevel = 0);
	// set number of life
	void setNumOfLevel(int numOfLife);
	// get number of life
	int getNumOfLevel() const;
	// increase level by one (postfix ++)
	NumLevelView& operator++(int);
	// decrease level by one (postfix --)
	NumLevelView& operator--(int);
	// convert to string
	virtual string toString() const override;
private:
	// number of life
	int m_numOfLevel;
	// check if number of life is legal
	bool isLegalLevel(int numOfLevel) const;
	// update level text
	void updateLevelText();
};


