//---- include section ------
#include "RectUtils.h"

sf::FloatRect RectUtils::createFloatRect(const sf::Vector2f& position, int width, int height)
{
	return sf::FloatRect(position.x, position.y, (float) width, (float) height);
}

sf::IntRect RectUtils::createIntRect(const sf::FloatRect& floatRect)
{
	return sf::IntRect((int)floatRect.left, (int)floatRect.top, (int)floatRect.width, (int)floatRect.height);
}

bool RectUtils::rectInAnother(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
	return  ((rect1.left + rect1.width) <= (rect2.left + rect2.width) &&
			(rect1.left >= rect2.left) && (rect1.top >= rect2.top) &&
			(rect1.top + rect1.height) <= (rect2.top + rect2.height));
}
