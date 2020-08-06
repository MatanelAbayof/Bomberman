#pragma once
//---- include section ------
#include "ImageButton.h"
#include "StopWatch.h"

/* 
 * TimeLeftView class
*/
class TimeLeftView :
	public ImageButton
{
public:
	// constructor
	TimeLeftView(sf::RenderWindow& window);
	// set time left (time in milliseconds)
	void start(int time, std::function<void()> onFinish);
	// stop time
	void stop();
	// append time
	void append(int timeToAppend);
	// draw
	virtual void draw();
	// convert to string
	virtual string toString() const override;
private:
	//clock
	StopWatch m_timeLeft;
	//check if legal time
	bool isLegalTime(int time) const;
	// initialize components
	void initComponents();
	// update time
	void updateTime();
	// one second in milliseconed (default tick interval)
	static const int SECOND = 1000;
};

