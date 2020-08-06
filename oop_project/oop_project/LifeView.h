#pragma once
//---- include section ------
#include "HorizontalLayout.h"
#include "Resources.h"
#include "ImageView.h"

/*
 * LifeView class
 */
class LifeView :
	public HorizontalLayout
{
public:
	// constructor
	LifeView(sf::RenderWindow& window, int numOfLife = 0);
	// set number of life
	void setNumOfLife(int numOfLife);
	// get number of life
	int getNumOfLife() const;
	// check if not have life
	bool hasNoLife() const;
	// increase life by one (postfix ++)
	LifeView& operator++(int);
	// decrease life by one (postfix --)
	LifeView& operator--(int);
	// convert to string
	virtual string toString() const override;
private:
	// number of life
	int m_numOfLife;
	// lifes images views
	vector<std::unique_ptr<ImageView>> m_lifes;
	// check if number of life is legal
	bool isLegalLife(int numOfLife) const;
	// add one life view to HorizontalLayout
	void addOneLifeView();
	// initialize components
	void initComponents();
	// redeclaring scope of base class functions in private section of derived class
	using HorizontalLayout::addView;
	using HorizontalLayout::removeView;
};

