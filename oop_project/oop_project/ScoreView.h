#pragma once
//---- include section ------
#include "ImageButton.h"
#include "TextView.h"

/*
* ScoreView class
*/
class ScoreView :
	public ImageButton
{
public:
	// constractor
	ScoreView(sf::RenderWindow& window, int numOfScore = 0);
	// set num of score
	void setNumOfScore(int numOfScore);
	// get num of score
	int getNumOfScore() const;
	// overloading operator (postfix ++)
	ScoreView& operator++(int);
	// overloading operator (postfix --)
	ScoreView& operator--(int);
	// overloading operator +=
	ScoreView& operator+=(int numOfBombs);
	// overloading operator -=
	ScoreView& operator-=(int numOfBombs);
	// convert to string
	virtual string toString() const override;
private:
	// number of score
	int m_numOfScore;
	// check legal score
	bool isLegalScore(int numOfScore) const;
	// initialize components
	void initComponents();
	// redeclaring scope of base class functions in private section of derived class
	using ImageButton::setImage;
	using ImageButton::setText;
};

