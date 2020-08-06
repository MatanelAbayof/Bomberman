//---- include section ------
#include "ImageButton.h"

ImageButton::ImageButton(sf::RenderWindow& window, const ImageTexture& imageTexture, const string& text)
	: HorizontalLayout(window), m_image(window, imageTexture), m_text(window, text)
{
	initComponents();
}

void ImageButton::setImage(const ImageTexture& imageTexture)
{
	m_image.setImage(imageTexture);
}

ImageTexture ImageButton::getImage() const
{
	return m_image.getImage();
}

void ImageButton::setText(const string& text)
{
	m_text.setText(text);
}

string ImageButton::getText() const
{
	return m_text.getText();
}

void ImageButton::setTextColor(const sf::Color& textColor)
{
	m_text.setTextColor(textColor);
}

sf::Color ImageButton::getTextColor() const
{
	return m_text.getTextColor();
}

void ImageButton::setTextHAligment(TextView::TextHAlignment textHAl)
{
	m_text.setTextHAlignment(textHAl);
}

string ImageButton::toString() const
{
	return "ImageButton: " + HorizontalLayout::toString();
}

void ImageButton::initComponents()
{
	// set my border
	setBorder(Border(sf::Color::Black, 1));

	// set buttons border
	Border buttonBorder(sf::Color::Black, 1);

	addView(m_image, 0.6f);
	addView(m_text, 0.4f);
}
