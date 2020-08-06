#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

//---- using section --------
using std::string;

/*
 * StopWatch class
 */
class StopWatch
{
public:
	// constructor
	StopWatch();
	// start stopWatch
	void start(int time, std::function<void()> onFinish);
	//stop clock
	void stop();
	// append time (in milliseconds)
	void append(int timeToAppend);
	// get left time
	int getLeftTime() const;
	// check if stopWatch is active
	bool isActive() const;
	// check stopWatch
	void checkStopWatch();
	// set tick
	void setTickListener(int interval, std::function<void()> onTick);
	// convert to string
	virtual string toString() const;
private:
	// using clock for stopWatch
	sf::Clock m_finishClock, m_tickClock;
	//stop watch active
	bool m_active, m_tickActive;
	// time for finish and interval for tick
	int m_time, m_interval;
	// listeners
	std::function<void()> m_onFinish, m_onTick;
};

