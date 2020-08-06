#pragma once
//---- include section ------
#include "ImageButton.h"

/*
*  BombsView class
*/
class BombsView :
	public ImageButton
{
public:
	// constructor
	BombsView(sf::RenderWindow& window, int numOfBombs = 0);
	// set num of Bombs
	void setNumOfBombs(int numOfBombs);
	// get num of bombs
	int getNumOfBombs() const;
	// has bombs
	bool hasBombs() const;
	// overloading operator (postfix ++)
	BombsView& operator++(int);
	// overloading operator (postfix --)
	BombsView& operator--(int);
	// overloading operator +=
	BombsView& operator+=(int numOfBombs);
	// overloading operator -=
	BombsView& operator-=(int numOfBombs);
	// convert to string
	virtual string toString() const override;
private:
	// number of bombs
	int m_numOfBombs;
	// check if number of bomb is legal
	bool isLegalBombs(int numOfBombs) const;
	// initialize components
	void initComponents();
	// redeclaring scope of base class functions in private section of derived class
	using ImageButton::setImage;
	using ImageButton::setText;
};


