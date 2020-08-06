#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>

//---- using section --------
using std::string;

/*
 * Border class
 */
class Border
{
public:
	// constructor (0 - no border)
	Border(const sf::Color& color = sf::Color(), int size = 0);
	// set color
	void setColor(const sf::Color &color);
	// get color
	sf::Color getColor() const;
	// set size
	void setSize(int size);
	// get size
	int getSize() const;
	// draw
	void draw(sf::RenderWindow& window, const sf::FloatRect& bound);
	// convert to string
	virtual string toString() const;
private:
	// color
	sf::Color m_color;
	// size (thickness of border)
	int m_size;
};

