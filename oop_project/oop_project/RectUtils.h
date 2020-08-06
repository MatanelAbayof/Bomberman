#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>

/*
 * RectUtils namespace
 */
namespace RectUtils {
	// create float rectangle
	sf::FloatRect createFloatRect(const sf::Vector2f& position, int width, int height);
	// create integer rectangle
	sf::IntRect createIntRect(const sf::FloatRect& floatRect);
	// check if rect1 in rect2
	bool rectInAnother(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
}
