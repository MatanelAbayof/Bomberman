#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>

//---- using section --------
using std::string;

/*
 * ImageTexture class
 */
class ImageTexture
{
public:
	// constructors
	ImageTexture();
	ImageTexture(const sf::Color &color);
	ImageTexture(sf::Texture &texture);
	// load mode options
	enum LoadMode {
		TEXTURE, COLOR
	};
	// get load mode
	LoadMode getLoadMode() const;
	// get texture
	sf::Texture& getTexture() const;
	// set texture
	void setTexture(sf::Texture& texture);
	// get color
	sf::Color getColor() const;
	// set color
	void setColor(const sf::Color& color);
	// draw
	void draw(sf::RenderWindow& window, const sf::FloatRect& bound);
	// convert to string
	virtual string toString() const;
private:
	// load mode of image texture 
	LoadMode m_loadMode;
	// image texture
	sf::Texture *m_texture;
	// color of image
	sf::Color m_color;
};

