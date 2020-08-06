//---- include section ------
#include "Border.h"

Border::Border(const sf::Color& color, int size)
	: m_color(color)
{
	setSize(size);
}

void Border::setColor(const sf::Color& color)
{
	m_color = color;
}

sf::Color Border::getColor() const
{
	return m_color;
}

void Border::setSize(int size)
{
	if (size < 0)
		throw string("Size of border (=" + std::to_string(size) + ") must be a natural number");
	m_size = size;
}

int Border::getSize() const
{
	return m_size;
}

void Border::draw(sf::RenderWindow& window, const sf::FloatRect& bounds)
{
	if ((m_size > 0)&&(bounds.width > 0)&&(bounds.height > 0)&&(m_color != sf::Color::Transparent)) {
		sf::RectangleShape borderShape;
		borderShape.setPosition(sf::Vector2f(bounds.left + m_size, bounds.top + m_size));
		borderShape.setSize(sf::Vector2f(bounds.width - 2*m_size, bounds.height - 2*m_size));
		borderShape.setFillColor(sf::Color::Transparent);
		borderShape.setOutlineThickness((float) m_size);
		borderShape.setOutlineColor(m_color);
		window.draw(borderShape);
	}	
}

string Border::toString() const
{
	return "Border: color=" + std::to_string(m_color.toInteger()) + ", size=" + std::to_string(m_size);
}
