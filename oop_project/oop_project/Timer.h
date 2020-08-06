#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

//---- using section --------
using std::string;

/*
 * Timer class
 */
class Timer
{
public:
	// constructor
	Timer();
	// check if timer is active
	bool isActive() const;
	// start timer. interval in milliseconds
	void start(int interval, std::function<void()> onTick);
	// get interval
	int getInterval() const;
	// stop timer
	void stop();
	// check timer (need this, because is run in same thread)
	void checkTimer();
	// convert to string
	virtual string toString() const;
private:
	// using clock for timer
	sf::Clock m_clock;
	// timer active
	bool m_active;
	// in milliseconds
	int m_interval;
	// function to call on tick
	std::function<void()> m_onTick;
};

