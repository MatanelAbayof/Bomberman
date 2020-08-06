//---- include section ------
#include "StopWatch.h"

StopWatch::StopWatch()
	: m_active(false), m_time(0), m_interval(0), m_onFinish(nullptr), m_onTick(nullptr), m_tickActive(false)
{ }

void StopWatch::start(int time, std::function<void()> onFinish)
{
	if (time < 0)
		throw string("Time must be bigger than zero (=" + std::to_string(time) + ")");
	m_active = true;
	m_onFinish = onFinish;
	m_time = time;	
	m_finishClock.restart();
}

void StopWatch::stop()
{
	m_active = false;
	m_tickActive = false;
}

void StopWatch::append(int timeToAppend)
{
	m_time += timeToAppend;
}

int StopWatch::getLeftTime() const
{
	return m_time - m_finishClock.getElapsedTime().asMilliseconds();
}

bool StopWatch::isActive() const
{
	return m_active;
}

void StopWatch::checkStopWatch()
{
	if (m_active) {
		if (m_tickActive) {
			if (m_tickClock.getElapsedTime().asMilliseconds() >= m_interval) {
				m_onTick();
				m_tickClock.restart();
			}
		}		
		if (m_finishClock.getElapsedTime().asMilliseconds() >= m_time) {
			m_onFinish();
			stop();
		}	
	}	
}

void StopWatch::setTickListener(int interval, std::function<void()> onTick)
{
	if (interval <= 0)
		throw string("Time must be bigger than zero");

	m_interval = interval;
	m_tickActive = true;
	m_onTick = onTick;
	m_tickClock.restart();
}

string StopWatch::toString() const
{
	return "StopWatch: active=" + std::to_string(m_active) + ", tickActive=" + std::to_string(m_tickActive);
}