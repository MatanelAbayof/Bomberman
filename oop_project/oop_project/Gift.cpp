//---- include section ------
#include "Gift.h"
#include "Resources.h"

Gift::Gift(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f & relPos,
	       const sf::Vector2f & relSize, GiftType giftType)
	: StaticCharacter(window, levelScreen, GIFT_DRAW_PRIORITY, relPos, relSize), m_giftType(giftType), m_giftState(CLOSE)
{
	init();
}

Gift::Gift(sf::RenderWindow & window, LevelScreen & levelScreen, const Cell & cell, 
	       const sf::Vector2f & relSize, GiftType giftType)
	: StaticCharacter(window, levelScreen, GIFT_DRAW_PRIORITY, cell, relSize), m_giftType(giftType), m_giftState(CLOSE)
{
	init();
}

void Gift::setGiftState(GiftState giftState)
{
	m_giftState = giftState;
}

Gift::GiftState Gift::getGiftState() const
{
	return m_giftState;
}

Gift::GiftType Gift::getGiftType() const
{
	return m_giftType;
}

void Gift::setGiftType(GiftType giftType)
{
	m_giftType = giftType;
}

Gift::GiftType Gift::randGiftType(short allowedGifts)
{
	short randNum; // random number between 0 to num of gifts - 1
	short giftTypeInt; // gift type (binary number)

	do {
		randNum = static_cast<short>(rand() % NUM_OF_GIFT_TYPE);
		giftTypeInt = ((short) 1) << randNum; // convert random number to gift type
	}
	while ((allowedGifts & giftTypeInt) == 0); // while gift type is not in allowed types
	// convert gift type integer to gift type enum
	GiftType giftType = static_cast<GiftType>(giftTypeInt);
	return giftType;
}

void Gift::draw()
{
	if(m_pickedStoper.isActive())
		m_pickedStoper.checkStopWatch();

	StaticCharacter::draw();
}

string Gift::toString() const
{
	return "Gift: giftType=" + giftTypeToStr(m_giftType) + ", " + StaticCharacter::toString();
}

std::unique_ptr<Character> Gift::clone()
{
	return std::make_unique<Gift>(*this);
}

void Gift::onCollide(Character& character)
{
	character.onCollide(*this);
}

void Gift::onCollide(Guard& character)
{
}

void Gift::onCollide(Player& character)
{
	if (m_giftState == GiftState::CLOSE) {
		m_giftState = GiftState::OPEN;
		setTextures(Resources::Animations::OpenGift); // show open gift animation
		setAnimationFrequency(75); // 300/4 = 75
		m_giftOpenSound.play();
		m_pickedStoper.start(300, [this]() { // kill me after 300 millis
			this->killMySelf();
		});		
	}	
}

void Gift::onCollide(Wall& character)
{
}

void Gift::onCollide(Bomb& character)
{
}

void Gift::onCollide(Rock& character)
{
}

void Gift::onCollide(ExitDoor& character)
{
}

void Gift::onCollide(Gift& character)
{
}

void Gift::onCollide(BlowingUpBomb& character)
{
}

void Gift::init()
{
	setImage(ImageTexture(Resources::Animations::OpenGift[0]));

	// load sound
	m_giftOpenSound.setBuffer(Resources::Sounds::GiftOpen);
}

string Gift::giftTypeToStr(GiftType giftType)
{
	string str;

	switch (giftType)
	{
		case Gift::GiftType::BOMB: {
			str = "Bomb";
		} break;
		case Gift::GiftType::LIFE: {
			str = "Life";
		} break;
		case Gift::GiftType::SCORE: {
			str = "Score";
		} break;
		case Gift::GiftType::TIME: {
			str = "Time";
		} break;
		case Gift::GiftType::SPEED: {
			str = "Speed";
		} break;
	}

	return str;
}
