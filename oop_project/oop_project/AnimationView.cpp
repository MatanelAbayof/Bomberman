//---- include section ------
#include "AnimationView.h"

AnimationView::AnimationView(sf::RenderWindow& window)
	: View(window), m_currentImageIndex(0)
{ }

AnimationView::AnimationView(AnimationView& anotherAnimView)
	: View(anotherAnimView) // copy the view part of another animation view
{
	// copy fields
	m_images = anotherAnimView.m_images;
	m_timer = anotherAnimView.m_timer;
	m_currentImageIndex = anotherAnimView.m_currentImageIndex;

	if (m_timer.getInterval() > 0) {
		// update animation frequency
		setAnimationFrequency(m_timer.getInterval());
	}
}

void AnimationView::setImage(const ImageTexture& imageTexture)
{
	clearAnimImages();
	m_images.push_back(imageTexture);
}

void AnimationView::addImage(const ImageTexture& imageTexture)
{
	m_images.push_back(imageTexture);
}

void AnimationView::setImages(std::vector<ImageTexture>& images)
{
	clearAnimImages();
	for (ImageTexture& imageTexture : images) {
		addImage(imageTexture);
	}
}

void AnimationView::setTextures(std::vector<sf::Texture>& images)
{
	clearAnimImages();
	for (sf::Texture& texture : images) {
		ImageTexture imageTexture(texture);
		addImage(imageTexture);
	}
}

void AnimationView::clearAnimImages()
{
	m_currentImageIndex = 0;
	m_images.clear();
}

void AnimationView::setAnimationFrequency(int frameMillis)
{
	// update timer
	m_timer.start(frameMillis, [this]() {
		if (this->m_currentImageIndex + 1 == this->m_images.size())
			this->m_currentImageIndex = 0;
		else
			this->m_currentImageIndex++;
	});
}

void AnimationView::stopAnimation()
{
	m_timer.stop();
}

void AnimationView::draw()
{
	View::draw();

	if (isShow()) {
		if (m_images.size() > 0) {
			// check timer before get current image
			m_timer.checkTimer();
			// draw current image
			getCurrentImage().draw(getWindow(), getBound());
		}
	}
}

string AnimationView::toString() const
{
	return "AnimationView: numOfImages=" + std::to_string(m_images.size()) + 
		   ", " + m_timer.toString() + ", " + View::toString();
}

ImageTexture& AnimationView::getCurrentImage()
{
	if (m_currentImageIndex + 1 > static_cast<int>(m_images.size()))
		throw string("No found image at index = " + std::to_string(m_currentImageIndex));
	return m_images[m_currentImageIndex];
}
