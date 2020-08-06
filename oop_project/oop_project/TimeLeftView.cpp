#include "TimeLeftView.h"
#include "Resources.h"

TimeLeftView::TimeLeftView(sf::RenderWindow& window)
	: ImageButton(window)
{
	initComponents();
}

void TimeLeftView::start(int time, std::function<void()> onFinish)
{
	if (!isLegalTime(time)) {
		throw string("time must be bigger or equals to zero (=" + std::to_string(time) + ")");
	}

	// update time when stop watch tick
	m_timeLeft.setTickListener(SECOND, [this]() {
		// update text
		this->updateTime();
	});

	// start stop watch
	m_timeLeft.start(time, onFinish);

	updateTime();
}

void TimeLeftView::stop()
{
	m_timeLeft.stop();
	setText("");
}

void TimeLeftView::append(int timeToAppend)
{
	m_timeLeft.append(timeToAppend);
}

void TimeLeftView::draw()
{
	m_timeLeft.checkStopWatch();
	ImageButton::draw();
}

string TimeLeftView::toString() const
{
	return "TimeLeftView: Time=" + std::to_string(m_timeLeft.getLeftTime());
}

bool TimeLeftView::isLegalTime(int time) const
{
	return (time >= 0);
}

void TimeLeftView::initComponents()
{
	setImage(Resources::Images::Watch);
	setTextHAligment(TextView::TextHAlignment::LEFT);
}

void TimeLeftView::updateTime()
{
	// if time less than 10 seconds
	if (this->m_timeLeft.getLeftTime() < 10000) {
		setTextColor(sf::Color::Red);
	}
	else {
		setTextColor(sf::Color(9, 105, 2));
	}
	int allLeftSeconds = m_timeLeft.getLeftTime() / SECOND;
	int leftMinutes = allLeftSeconds / 60;
	int leftSeconds = allLeftSeconds % 60;
	string leftSecondsStr = std::to_string(leftSeconds);
	if (leftSecondsStr.length() == 1)
		leftSecondsStr = "0" + leftSecondsStr;
	string timeText = std::to_string(leftMinutes) + ":" + leftSecondsStr;
	setText(timeText);
}
