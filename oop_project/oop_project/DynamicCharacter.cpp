//---- include section ------
#include "DynamicCharacter.h"
#include "LevelScreen.h"
#include "Utilities.h"
#include <algorithm>

// init
const float DynamicCharacter::MINIMUM_SPEED = 0.0f;

DynamicCharacter::DynamicCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority,
	                              const sf::Vector2f& relPos, const sf::Vector2f& relSize, float speed)
	: Character(window, levelScreen, drawPriority, relPos, relSize)
{ 
	setDirection(Direction::STANDING);
	setSpeed(speed);
}

DynamicCharacter::DynamicCharacter(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority,
	                              const Cell& cell, const sf::Vector2f& relSize, float speed)
	: Character(window, levelScreen, drawPriority, cell, relSize)
{
	setDirection(Direction::STANDING);
	setSpeed(speed);
}

void DynamicCharacter::setSpeed(float speed)
{
	if (!isLegalSpeed(speed))
		throw string("Speed must be bigger or equals to zero (=" + std::to_string(speed) + ")");
	m_speed = speed;
}

void DynamicCharacter::appendSpeed(float speed)
{
	setSpeed(m_speed + speed);
}

float DynamicCharacter::getSpeed() const
{
	return m_speed;
}

bool DynamicCharacter::hasNoSpeed() const
{
	return (m_speed == 0);
}

void DynamicCharacter::setDirection(Direction direction)
{
	m_direction = direction;
}

DynamicCharacter::Direction DynamicCharacter::getDirection() const
{
	return m_direction;
}

void DynamicCharacter::move(const sf::Vector2f& relativePosition)
{
	sf::Vector2f lastRPos = getRelativePosition();
	setRelativePosition(sf::Vector2f(lastRPos.x + relativePosition.x, lastRPos.y + relativePosition.y));
}

void DynamicCharacter::move(float x, float y)
{
	sf::Vector2f lastRPos = getRelativePosition();
	setRelativePosition(sf::Vector2f(lastRPos.x + x, lastRPos.y + y));
}


bool DynamicCharacter::canMove(const sf::Vector2f& relPos)
{
	// check if character in map bounds
	if (!Utilities::inLevelBounds(relPos, getRelativeSize()))
		return false;

	// calculate new bounds
	sf::FloatRect newBounds(relPos, getRelativeSize());

	// get matrix size
	LevelMap::CharsMatrix& charMatrix = getLevelScreen().getLevelMap().getCharsMatrix();
	int rows = charMatrix.getNumOfRows(), cols = charMatrix.getNumOfCols();

	// check collide characters by 9 closed cells
	Cell myCell = getCell();
	Cell checkCell = myCell;

	if (isCharsInCellCollide(checkCell, newBounds))
		return false;

	if(myCell.getRowNum() + 1 < rows) {
		checkCell = Cell(myCell.getRowNum() + 1, myCell.getColNum());
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if (myCell.getRowNum() - 1 >= 0) {
		checkCell = Cell(myCell.getRowNum() - 1, myCell.getColNum());
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if (myCell.getColNum() + 1 < cols) {
		checkCell = Cell(myCell.getRowNum(), myCell.getColNum() + 1);
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if (myCell.getColNum() - 1 >= 0) {
		checkCell = Cell(myCell.getRowNum(), myCell.getColNum() - 1);
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if ((myCell.getRowNum() - 1 >= 0)&&(myCell.getColNum() - 1 >= 0)) {
		checkCell = Cell(myCell.getRowNum() - 1, myCell.getColNum() - 1);
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if ((myCell.getRowNum() + 1 < rows) && (myCell.getColNum() + 1 < cols)) {
		checkCell = Cell(myCell.getRowNum() + 1, myCell.getColNum() + 1);
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if ((myCell.getRowNum() - 1 >= 0) && (myCell.getColNum() + 1 < cols)) {
		checkCell = Cell(myCell.getRowNum() - 1, myCell.getColNum() + 1);
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	if ((myCell.getRowNum() + 1 < rows) && (myCell.getColNum() - 1 >= 0)) {
		checkCell = Cell(myCell.getRowNum() + 1, myCell.getColNum() - 1);
		if (isCharsInCellCollide(checkCell, newBounds))
			return false;
	}

	return true;
}

sf::Vector2f DynamicCharacter::requestNextPosition()
{
	if ((m_direction == Direction::STANDING) || hasNoSpeed()) {
		m_clock.restart();
		return getRelativePosition();
	}

	// get character matrix
	LevelMap::CharsMatrix& charMatrix = getLevelScreen().getLevelMap().getCharsMatrix();

	// find new position
	float dx = 0, dy = 0;
	switch (m_direction)
	{
		case Direction::RIGHT: {
			dx = (m_speed/(float)charMatrix.getNumOfCols()) * m_clock.getElapsedTime().asSeconds();
		} break;
		case Direction::LEFT: {
			dx = -(m_speed / (float)charMatrix.getNumOfCols()) * m_clock.getElapsedTime().asSeconds();
		} break;
		case Direction::UP: {
			dy = -(m_speed / (float)charMatrix.getNumOfRows()) * m_clock.getElapsedTime().asSeconds();
		} break;
		case Direction::DOWN: {
			dy = (m_speed / (float)charMatrix.getNumOfRows()) * m_clock.getElapsedTime().asSeconds();
		} break;
	}
	m_clock.restart();

	return sf::Vector2f(getRelativePosition().x + dx, getRelativePosition().y + dy);
}

bool DynamicCharacter::isCharInMyCollideM(const Character& character) const
{
	return std::find(m_collideCharacters.begin(), m_collideCharacters.end(), string(typeid(character).name())) != m_collideCharacters.end();
}


void DynamicCharacter::addCollideCharacterType(const string& charType)
{
	m_collideCharacters.push_back(charType);
}

void DynamicCharacter::draw()
{
	// play before draw
	play();

	Character::draw();
}

string DynamicCharacter::toString() const
{
	return "DynamicCharacter: speed=" + std::to_string(m_speed) + ", direction=" + 
		   directionToStr(m_direction) + ", " + Character::toString();
}

bool DynamicCharacter::isLegalSpeed(float speed) const
{
	return (speed >= MINIMUM_SPEED);
}

string DynamicCharacter::directionToStr(Direction direction) const
{
	string dirStr;
	switch (direction)
	{
		case Direction::RIGHT: {
			dirStr = "right";
		} break;
		case Direction::LEFT: {
			dirStr = "left";
		} break;
		case Direction::UP: {
			dirStr = "up";
		} break;
		case Direction::DOWN: {
			dirStr = "down";
		} break;
		case Direction::STANDING: {
			dirStr = "standing";
		} break;
	}
	return dirStr;
}

bool DynamicCharacter::isCharsInCellCollide(const Cell& cell, const sf::FloatRect& bounds)
{
	std::list<Character*>& charsInCell = getLevelScreen().getLevelMap().getCharsMatrix().getCellData(cell);
	for (std::list<Character*>::iterator it = charsInCell.begin(); it != charsInCell.end(); ++it) {
		Character& character = (*(*it));
		// if character it not me
		if (&character != this) {
			// check if character collide me
			if (character.getRBounds().intersects(bounds)) {
				// check if character in my "collide characters"
				if (isCharInMyCollideM(character))
					return true;
			}
		}
	}
	return false;
}
