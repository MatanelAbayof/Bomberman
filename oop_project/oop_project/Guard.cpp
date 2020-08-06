//---- include section ------
#include "Guard.h"
#include "Resources.h"
#include "Wall.h"
#include "Rock.h"
#include "LevelScreen.h"

Guard::Guard(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: DynamicCharacter(window, levelScreen, GUARD_DRAW_PRIORITY, relPos, relSize), m_healfh(HealthState::LIVE)
{
	init();
}

Guard::Guard(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell, const sf::Vector2f& relSize)
	: DynamicCharacter(window, levelScreen, GUARD_DRAW_PRIORITY, cell, relSize), m_healfh(HealthState::LIVE)
{
	init();
}

void Guard::setDirection(Direction direction)
{
	if (getDirection() == direction)
		return;

	DynamicCharacter::setDirection(direction);

	// update animation
	switch (direction)
	{
		case DynamicCharacter::RIGHT: {
			setTextures(Resources::Animations::GuardRightDir);
			setAnimationFrequency(GUARD_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::LEFT: {
			setTextures(Resources::Animations::GuardLeftDir);
			setAnimationFrequency(GUARD_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::UP: {
			setTextures(Resources::Animations::GuardTopDir);
			setAnimationFrequency(GUARD_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::DOWN: {
			setTextures(Resources::Animations::GuardDownDir);
			setAnimationFrequency(GUARD_ANIM_FREQUENCY);
		} break;
		case DynamicCharacter::STANDING: {
			stopAnimation();
		} break;
	}
}

DynamicCharacter::Direction Guard::getRandomDirect() const
{
	int num = rand() % NUM_OF_DIRECTIONS;
	Direction direct = static_cast<Direction>(num);
	return direct;
}

DynamicCharacter::Direction Guard::getHRandomDirect() const
{
	return (rand() % 2 == 0) ? Direction::LEFT : Direction::RIGHT;
}

DynamicCharacter::Direction Guard::getVRandomDirect() const
{
	return (rand() % 2 == 0) ? Direction::UP : Direction::DOWN;
}

string Guard::toString() const
{
	return string ("Guard: " + DynamicCharacter::toString());
}

Guard::HealthState Guard::getHealthState() const
{
	return m_healfh;
}

Guard::GuardType Guard::randGuardType()
{
	int num = rand() % 2;
	Guard::GuardType guardType = static_cast<Guard::GuardType>(num);
	return guardType;
}

void Guard::onCollide(Character & character)
{
	character.onCollide(*this);
}

void Guard::onCollide(Guard& character)
{
}

void Guard::onCollide(Player& character)
{
}

void Guard::onCollide(Wall& character)
{
}

void Guard::onCollide(Bomb& character)
{
}

void Guard::onCollide(Rock& character)
{
}

void Guard::onCollide(ExitDoor& character)
{
}

void Guard::onCollide(Gift& character)
{
}

void Guard::onCollide(BlowingUpBomb& character)
{
	if (m_healfh == HealthState::LIVE) {
		int numOfGuards = getLevelScreen().getLevelMap().getNumOfGuards();
		getLevelScreen().getGameMenu().getScoreView() += SCORE_FOR_KILL_GUARD * numOfGuards;

		// ready to die
		readyToDie();
	}	
}

void Guard::draw()
{
	if (m_dieStoper.isActive())
		m_dieStoper.checkStopWatch();
	DynamicCharacter::draw();
}

void Guard::init()
{
	setDirection(DynamicCharacter::Direction::LEFT);

	m_dieSound.setBuffer(Resources::Sounds::AnimalDie);

	// add collide characters types
	addCollideCharacterType(typeid(Wall).name());
	addCollideCharacterType(typeid(Rock).name());
}

void Guard::readyToDie()
{
	m_healfh = HealthState::READY_TO_DIE;

	// change animation
	setTextures(Resources::Animations::GuardDie);
	setAnimationFrequency(84); // 500/6 ~ 84

	// play sound
	m_dieSound.play();

	// die after half second
	m_dieStoper.setTickListener(50, [this]() {
		if (this->getSpeed() - 0.1f > 0)
			this->appendSpeed(-0.1f);
	});
	m_dieStoper.start(500, [this]() {
		this->killMySelf();
	});
}
