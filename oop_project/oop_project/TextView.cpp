//---- include section ------
#include "TextView.h"
#include "Utilities.h"
#include "Resources.h"

TextView::TextView(sf::RenderWindow& window, const string& text)
			: View(window), m_textHAlign(CENTER)
{
	// init text object
	setFont(Resources::Fonts::Arial); // default font
	m_text.setCharacterSize(17);
	m_text.setFillColor(sf::Color::Black);
	setText(text);
}

string TextView::getText() const
{
	return m_text.getString();
}

void TextView::setText(const string &text)
{
	m_text.setString(text);
	updateComponents();
}

void TextView::setTextColor(const sf::Color& textColor)
{
	m_textColor = textColor;
	m_text.setFillColor(m_textColor);
}

sf::Color TextView::getTextColor() const
{
	return m_textColor;
}

void TextView::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void TextView::setTextHAlignment(TextHAlignment textHAlign)
{
	m_textHAlign = textHAlign;
	updateComponents();
}

void TextView::setTextSize(unsigned int textSize)
{
	m_text.setCharacterSize(textSize);
	updateComponents();
}

unsigned int TextView::getTextSize() const
{
	return m_text.getCharacterSize();
}

TextView::TextHAlignment TextView::getTextHAlignment() const
{
	return m_textHAlign;
}

void TextView::draw()
{
	View::draw();
	sendDrawRequest(m_text);
}

string TextView::toString() const
{
	return "TextView: text=" + m_text.getString() + ", " + View::toString();
}

void TextView::updateComponents()
{
	View::updateComponents();

	if (isNoSet())
		return;

	// reset position & scale
	m_text.setPosition(getPosition());
	m_text.setScale(1, 1);

	// resize text (do like this becuse we dont want to 'spread' the text with scaling)
	while (m_text.getGlobalBounds().height > getBound().height) {
		float newScaleY = m_text.getScale().y - 0.1f;
		if (newScaleY < 0)
			break; // No enough space!
		m_text.setScale(m_text.getScale().x, newScaleY);
	}
	while (m_text.getGlobalBounds().width > getBound().width) {
		float newScaleX = m_text.getScale().x - 0.1f;
		if (newScaleX < 0)
			break; // No enough space!
		m_text.setScale(newScaleX, m_text.getScale().y);
	}

	// margin text to center
	float dHeight = getBound().height - m_text.getGlobalBounds().height;
	switch (m_textHAlign)
	{
		case RIGHT: {
			m_text.setPosition(sf::Vector2f(getPosition().x + getBound().width - m_text.getGlobalBounds().width,
				getPosition().y + dHeight / 2));
		} break;
		case LEFT: {
			m_text.setPosition(sf::Vector2f(getPosition().x,
				getPosition().y + dHeight / 2));
		} break;
		case CENTER: {
			float dWidth = getBound().width - m_text.getGlobalBounds().width;
			m_text.setPosition(sf::Vector2f(getPosition().x + dWidth / 2,
				getPosition().y + dHeight / 2));
		} break;
	}
}
