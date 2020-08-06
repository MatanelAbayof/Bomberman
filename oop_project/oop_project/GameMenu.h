#pragma once
//---- include section ------
#include "HorizontalLayout.h"
#include "ScoreView.h"
#include "BombsView.h"
#include "TimeLeftView.h"
#include "LifeView.h"
#include "TextView.h"
#include "NumLevelView.h"

/*
* GameMenu class
*/
class GameMenu :
	public HorizontalLayout
{
public:
	//constractor
	GameMenu(sf::RenderWindow & window);
	// get scoreView
	ScoreView& getScoreView();
	// get life view
	LifeView& getLifeview();
	// get bombs view
	BombsView& getBombsView();
	//get time left view
	TimeLeftView& getTimeLeftView();
	// get num level
	NumLevelView& getNumLevelView();
	// get restartButton
	TextView& getRestartButton();
	// set restartButton
	void setRestartButton();
	// clear
	void clear();
	// convert to string
	virtual string toString() const override;
private:
	// num of score
	ScoreView m_scoreView;
	// num of life
	LifeView m_lifeView;
	// num of bombs
	BombsView m_bombsView;
	// time left 
	TimeLeftView m_timeLeftView;
	// number level
	NumLevelView m_numLevelView;
	//for restart level
	TextView m_restartButton;
	// initial components
	void initComponents();
	// init
	void init(ImageButton &ImageButton);
	//initial textView
	void initTextView(TextView &textView);
	//initial lifeView
	void initLifeView(LifeView &liveView);
	// redeclaring scope of base class functions in private section of derived class
	using HorizontalLayout::addView;
	using HorizontalLayout::removeView;
};

