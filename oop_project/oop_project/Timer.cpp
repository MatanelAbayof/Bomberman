//---- include section ------
#include "Timer.h"

Timer::Timer()
	: m_active(false), m_interval(0), m_onTick(nullptr)
{ }

bool Timer::isActive() const
{
	return m_active;
}

void Timer::start(int interval, std::function<void()> onTick)
{
	if (interval <= 0)
		throw string("Interval must be bigger than zero");

	m_interval = interval;
	m_onTick = onTick;
	m_active = true;
	m_clock.restart();
}

int Timer::getInterval() const
{
	return m_interval;
}

void Timer::stop()
{
	m_active = false;
}

void Timer::checkTimer()
{
	if (m_active) {
		// check if time to wake up...
		if (m_clock.getElapsedTime().asMilliseconds() > m_interval) {
			m_clock.restart();
			// call tick event
			m_onTick();
		}		
	}
}

string Timer::toString() const
{
	return "Timer: active=" + std::to_string(m_active) + ", interval=" + std::to_string(m_interval);
}
