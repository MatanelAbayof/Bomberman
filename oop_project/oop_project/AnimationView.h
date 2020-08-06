#pragma once
//---- include section ------
#include "View.h"
#include "Timer.h"

/*
 * AnimationView class
 */
class AnimationView :
	public View
{
public:
	// constructor
	AnimationView(sf::RenderWindow& window);
	// copy constructor
	AnimationView(AnimationView& anotherAnimView);
	// set image in animation
	void setImage(const ImageTexture& imageTexture);
	// add new image to animation
	void addImage(const ImageTexture& imageTexture);
	// set images in animation
	void setImages(std::vector<ImageTexture>& images);
	// set images to animation
	void setTextures(std::vector<sf::Texture>& images);
	// clear animation images
	void clearAnimImages();
	// set animation frequency - get time in milliseconds to one frame
	void setAnimationFrequency(int frameMillis);
	// stop animation
	void stopAnimation();
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
private:
	// images in animation
	vector<ImageTexture> m_images;
	// current image index
	int m_currentImageIndex;
	// timer for frames
	Timer m_timer;
	// get current image
	ImageTexture& getCurrentImage();
};

