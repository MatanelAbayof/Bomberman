#pragma once
//---- include section ------
#include "View.h"
#include <string>

//---- using section --------
using std::string;

class ImageView :
	public View
{
public:
	// constructor
	ImageView(sf::RenderWindow& window, const ImageTexture& imageTexture = ImageTexture());
	// set image
	void setImage(const ImageTexture& imageTexture);
	// get image
	ImageTexture getImage() const;
	// draw in window
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
private:
	// image texture
	ImageTexture m_image;
};

