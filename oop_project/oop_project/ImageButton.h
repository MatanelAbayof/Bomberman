#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "ImageView.h"
#include "TextView.h"
//---- using section --------
using std::string;

/*
 * ImageButtom class
 */
class ImageButton :
	public HorizontalLayout
{
public:
	// constructor
	ImageButton(sf::RenderWindow& window, const ImageTexture& imageTexture = ImageTexture(), const string& text = "");
	// set image
	void setImage(const ImageTexture& imageView);
	// get image
	ImageTexture getImage() const;
	// set text
	void setText(const string &text);
	// get text
	string getText() const;
	// set text colot
	void setTextColor(const sf::Color& textColor);
	// get text color
	sf::Color getTextColor() const;
	// set text horizontal alignment
	void setTextHAligment(TextView::TextHAlignment textAlignment);
	// convert to string
	virtual string toString() const override;
private:
	// image
	ImageView m_image;
	// text
	TextView m_text;
	// init components
	void initComponents();
	// redeclaring scope of base class functions in private section of derived class
	using HorizontalLayout::addView;
	using HorizontalLayout::removeView;
};

