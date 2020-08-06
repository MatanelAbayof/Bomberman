//---- include section ------
#include "BlowingUpBomb.h"
#include "Resources.h"

BlowingUpBomb::BlowingUpBomb(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, BUB_DRAW_PRIORITY, relPos, relSize)
{
	init();
}

BlowingUpBomb::BlowingUpBomb(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, BUB_DRAW_PRIORITY, cell, relSize)
{
	init();
}

BlowingUpBomb::BlowingUpBomb(BlowingUpBomb& anotherBub)
	: StaticCharacter(anotherBub)
{
	m_stoper = anotherBub.m_stoper;
	init();
}

void BlowingUpBomb::draw()
{
	if (m_firstDraw) {
		m_bubSound.play();
		m_firstDraw = false;
	}
	m_stoper.checkStopWatch();
	StaticCharacter::draw();
}

string BlowingUpBomb::toString() const
{
	return "BlowingUpBomb: " + StaticCharacter::toString();
}

std::unique_ptr<Character> BlowingUpBomb::clone()
{
	return std::make_unique<BlowingUpBomb>(*this);
}

void BlowingUpBomb::onCollide(Character& character)
{
	character.onCollide(*this);
}

void BlowingUpBomb::onCollide(Guard& character)
{
}

void BlowingUpBomb::onCollide(Player& character)
{
}

void BlowingUpBomb::onCollide(Wall& character)
{
}

void BlowingUpBomb::onCollide(Bomb& character)
{
}

void BlowingUpBomb::onCollide(Rock& character)
{
}

void BlowingUpBomb::onCollide(ExitDoor& character)
{
}

void BlowingUpBomb::onCollide(Gift& character)
{
}

void BlowingUpBomb::onCollide(BlowingUpBomb& character)
{
}

void BlowingUpBomb::init()
{
	m_firstDraw = true;
	// load sound
	m_bubSound.setBuffer(Resources::Sounds::Explosion);
	m_bubSound.setPitch(2.f);
	// load animation
	setTextures(Resources::Animations::Explosion);
	setAnimationFrequency(31); // 500/16 ~ 31 (500 millis, 16 frames)
	m_stoper.start(500, [this]() {
		
		this->killMySelf();
	});
}
