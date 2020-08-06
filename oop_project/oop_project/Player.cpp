//---- include section ------
#include "Player.h"
#include "Resources.h"
#include "Bomb.h"
#include "LevelScreen.h"
#include "Wall.h"
#include "Rock.h"
#include "Gift.h"
#include "Guard.h"

// init
const float Player::APPEND_SPEED_GIFT = 0.5f;

Player::Player(sf::RenderWindow& window, LevelScreen& levelScreen, 
	           const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: DynamicCharacter(window, levelScreen, PLAYER_DRAW_PRIORITY, relPos, relSize), m_dieHandler(nullptr), m_endLevelHandler(nullptr)
{
	init();
}

Player::Player(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell, const sf::Vector2f& relSize)
	: DynamicCharacter(window, levelScreen, PLAYER_DRAW_PRIORITY, cell, relSize), m_dieHandler(nullptr), m_endLevelHandler(nullptr)
{
	init();
}

void Player::setDirection(Direction direction)
{
	if (getDirection() == direction)
		return;

	DynamicCharacter::setDirection(direction);

	// update animation
	switch (direction)
	{
		case DynamicCharacter::RIGHT: {		
			setTextures(Resources::Animations::RobotRightDir);
			setAnimationFrequency(PLAYER_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::LEFT: {
			setTextures(Resources::Animations::RobotLeftDir);
			setAnimationFrequency(PLAYER_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::UP: {
			setTextures(Resources::Animations::RobotUpDir);
			setAnimationFrequency(PLAYER_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::DOWN: {
			setTextures(Resources::Animations::RobotDownDir);
			setAnimationFrequency(PLAYER_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::STANDING: {
			stopAnimation();
		} break;
	}
}

void Player::play()
{
	sf::Vector2f nextPosition = requestNextPosition();
	if (canMove(nextPosition))
		setRelativePosition(nextPosition);
	else {
		setDirection(DynamicCharacter::Direction::STANDING);
	}
}

void Player::handleKeyPressed(const sf::Keyboard::Key& keyCode)
{
	switch (keyCode)
	{
		case sf::Keyboard::Up: {
			setDirection(DynamicCharacter::Direction::UP);
		} break;
		case sf::Keyboard::Down: {
			setDirection(DynamicCharacter::Direction::DOWN);
		} break;
		case sf::Keyboard::Right: {
			setDirection(DynamicCharacter::Direction::RIGHT);
		} break;
		case sf::Keyboard::Left: {
			setDirection(DynamicCharacter::Direction::LEFT);
		} break;
	}
}

void Player::handleKeyReleased(const sf::Keyboard::Key& keyCode)
{
	switch (keyCode)
	{
		case sf::Keyboard::Up:
		case sf::Keyboard::Down:
		case sf::Keyboard::Right:
		case sf::Keyboard::Left: {
			setDirection(DynamicCharacter::Direction::STANDING);
		} break;
		case sf::Keyboard::B: {
			createBomb();
		} break;
	}
}

string Player::toString() const
{
	return "Player: " + DynamicCharacter::toString();
}

void Player::setOnEndLevelListener(std::function<void()> onEndLevel)
{
	m_endLevelHandler = onEndLevel;
}

void Player::setOnDieListener(std::function<void()> onDieListener)
{
	m_dieHandler = onDieListener;
}

std::unique_ptr<Character> Player::clone()
{
	return std::make_unique<Player>(*this);
}

void Player::onCollide(Character& character)
{
	character.onCollide(*this);
}

void Player::onCollide(Guard& guard)
{
	if(guard.getHealthState() == Guard::HealthState::LIVE)
		callDieEvent();
}

void Player::onCollide(Player& character)
{
}

void Player::onCollide(Wall& character)
{
}

void Player::onCollide(Bomb& character)
{
}

void Player::onCollide(Rock& character)
{
}

void Player::onCollide(ExitDoor& character)
{
	callEndLevelEvent();
}

void Player::onCollide(Gift& gift)
{
	if (gift.getGiftState() == Gift::GiftState::CLOSE) {
		switch (gift.getGiftType())
		{
			case Gift::GiftType::BOMB: {
				getLevelScreen().getGameMenu().getBombsView() += BOMB_GIFT;
			} break;
			case Gift::GiftType::LIFE: {
				getLevelScreen().getGameMenu().getLifeview()++;
			} break;
			case Gift::GiftType::SCORE: {
				getLevelScreen().getGameMenu().getScoreView() += SCORE_GIFT;
			} break;
			case Gift::GiftType::TIME: {
				getLevelScreen().getGameMenu().getTimeLeftView().append(TIME_GIFT);
			} break;
			case Gift::GiftType::SPEED: {
				appendSpeed(APPEND_SPEED_GIFT);
			} break;
		}
	}	
}

void Player::onCollide(BlowingUpBomb& character)
{
	callDieEvent();
}

void Player::init()
{
	setImage(ImageTexture(Resources::Animations::RobotDownDir[0]));
	setSpeed(2.1f);

	// add collide characters types
	addCollideCharacterType(typeid(Wall).name());
	addCollideCharacterType(typeid(Rock).name());
}

void Player::createBomb()
{
	// check if have bombs
	BombsView& bombsView = getLevelScreen().getGameMenu().getBombsView();
	if (bombsView.hasBombs() || (!getLevelScreen().isUseBombs())) {
		// create bomb
		Bomb bomb(getWindow(), getLevelScreen(), getRelativePosition(), getRelativeSize());
		getLevelScreen().getLevelMap().getCharacterList().requestAddCharacter(bomb);

		if(getLevelScreen().isUseBombs())
			bombsView--;
	}
}

void Player::callEndLevelEvent()
{
	if (m_endLevelHandler != nullptr)
		m_endLevelHandler();
}

void Player::callDieEvent()
{
	if (m_dieHandler != nullptr)
		m_dieHandler();
}
