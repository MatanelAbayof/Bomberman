//---- include section ------
#include "ImageView.h"

ImageView::ImageView(sf::RenderWindow& window, const ImageTexture& imageTexture)
	: View(window), m_image(imageTexture)
{ }

void ImageView::setImage(const ImageTexture& imageTexture)
{
	m_image = imageTexture;
}

ImageTexture ImageView::getImage() const
{
	return m_image;
}

void ImageView::draw()
{
	View::draw();

	if(isShow())
		m_image.draw(getWindow(), getBound());
}

string ImageView::toString() const
{
	return "ImageView: image=" + m_image.toString() + ", view=" + View::toString();
}
