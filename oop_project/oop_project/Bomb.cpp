//---- include section ------
#include "Bomb.h"
#include "Resources.h"
#include "BlowingUpBomb.h"
#include "LevelScreen.h"
#include "Utilities.h"

Bomb::Bomb(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, BOMB_DRAW_PRIORITY, relPos, relSize)
{
	init();
}

Bomb::Bomb(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell, const sf::Vector2f& relSize)
	: StaticCharacter(window, levelScreen, BOMB_DRAW_PRIORITY, cell, relSize)
{
	init();
}

Bomb::Bomb(Bomb& anotherBomb)
	: StaticCharacter(anotherBomb)
{
	m_stoper = anotherBomb.m_stoper;
	init();
}

string Bomb::toString() const
{
	return "Bomb: " + StaticCharacter::toString();
}

std::unique_ptr<Character> Bomb::clone()
{
	return std::make_unique<Bomb>(*this);
}

void Bomb::draw()
{
	m_stoper.checkStopWatch();
	if (m_bombTickSound.getStatus() != sf::SoundSource::Status::Playing)
		m_bombTickSound.play();
	StaticCharacter::draw();
}

void Bomb::onCollide(Character & character)
{
	character.onCollide(*this);
}

void Bomb::onCollide(Guard & character)
{
}

void Bomb::onCollide(Player & character)
{
}

void Bomb::onCollide(Wall & character)
{
}

void Bomb::onCollide(Bomb & character)
{
}

void Bomb::onCollide(Rock & character)
{
}

void Bomb::onCollide(ExitDoor & character)
{
}

void Bomb::onCollide(Gift & character)
{
}

void Bomb::onCollide(BlowingUpBomb & character)
{
}

void Bomb::init()
{
	// load animation
	setTextures(Resources::Animations::Bomb);
	setAnimationFrequency(1335); // 4000/3 ~ 1335

	// load sound
	m_bombTickSound.setBuffer(Resources::Sounds::BombTick);
	m_bombTickSound.setLoop(true);
	m_bombTickSound.setVolume(10);

	// timer before explode
	m_stoper.setTickListener(500, [this]() {
		this->m_bombTickSound.setPitch(this->m_bombTickSound.getPitch() + 0.05f); // increase sound speed
		if(this->m_bombTickSound.getVolume() + 5 <= 100) 
			this->m_bombTickSound.setVolume(this->m_bombTickSound.getVolume() + 5); // increase volume
	});
	m_stoper.start(4000, [this]() { 
		this->explode();
	});
}

void Bomb::explode()
{
	sf::Vector2f myPos = getRelativePosition();
	sf::Vector2f mySize = getRelativeSize();

	// add blowing up bomb
	tryAddBub(getRelativePosition());
	tryAddBub(sf::Vector2f(myPos.x + mySize.x, myPos.y));
	tryAddBub(sf::Vector2f(myPos.x, myPos.y + mySize.y));
	tryAddBub(sf::Vector2f(myPos.x - mySize.x, myPos.y));
	tryAddBub(sf::Vector2f(myPos.x, myPos.y - mySize.y));

	// kill my self
	killMySelf();
}

void Bomb::tryAddBub(const sf::Vector2f& relPos)
{
	// check if bomb in level bounds
	if(Utilities::inLevelBounds(relPos, getRelativeSize())) {
		// add BUB
		BlowingUpBomb bub(getWindow(), getLevelScreen(), relPos, getRelativeSize());
		getLevelScreen().getLevelMap().getCharacterList().requestAddCharacter(bub);
	}
}
