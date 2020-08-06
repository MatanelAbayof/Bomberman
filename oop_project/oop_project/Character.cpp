//---- include section ------
#include "Character.h"
#include "LevelScreen.h"
#include "Utilities.h"

Character::Character(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority,
	                 const sf::Vector2f& relPos, const sf::Vector2f& relSize)
	: AnimationView(window), m_levelScreen(levelScreen), m_drawPriority(drawPriority),
	  m_relativePosition(relPos), m_relativeSize(relSize), m_startRelPos(relPos), m_showInMap(false)
{
	init();	
}

Character::Character(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority, 
	                 const Cell& cell, const sf::Vector2f& relSize)
	: AnimationView(window), m_levelScreen(levelScreen), m_drawPriority(drawPriority),
	  m_relativeSize(relSize), m_relativePosition(Utilities::calcPositionByCell(levelScreen, cell)), 
	  m_startRelPos(m_relativePosition), m_showInMap(false)
{
	init();
}

Character::~Character()
{
	getLevelScreen().getLevelMap().getCharsMatrix().getCellData(m_myCell).remove(this);
}

Character::Character(Character& anotherCharacter)
	: AnimationView(anotherCharacter), m_levelScreen(anotherCharacter.m_levelScreen), m_startRelPos(anotherCharacter.m_startRelPos)
{
	m_drawPriority = anotherCharacter.m_drawPriority;
	m_relativePosition = anotherCharacter.m_relativePosition;
	m_relativeSize = anotherCharacter.m_relativeSize;
	m_myCell = anotherCharacter.m_myCell;
	init();
}

void Character::killMySelf()
{
	getLevelScreen().getLevelMap().getCharacterList().requestRemoveCharacter(*this);
}

int Character::getDrawPriority() const
{
	return m_drawPriority;
}

void Character::setCellLocation(const Cell& cell)
{
	setRelativePosition(Utilities::calcPositionByCell(getLevelScreen(), cell));
}

bool Character::isCollidedWithAnother(const Character& anotherCharacter) const
{
	return getBound().intersects(anotherCharacter.getBound());
}

void Character::setRelativePosition(const sf::Vector2f& relativePosition)
{
	m_relativePosition = relativePosition;
	// get level map position & size
	sf::Vector2f mapPosition = m_levelScreen.getLevelMap().getPosition();
	sf::Vector2i mapSize = m_levelScreen.getLevelMap().getSize();
	// set real position
	setPosition(sf::Vector2f(mapPosition.x + relativePosition.x*mapSize.x, mapPosition.y + relativePosition.y*mapSize.y));
	updateCharCell(false);
}

void Character::setRelativeSize(const sf::Vector2f& relativeSize)
{
	m_relativeSize = relativeSize;
	// get level map size
	sf::Vector2i mapSize = m_levelScreen.getLevelMap().getSize();
	// set real size
	setSize(sf::Vector2i((int)(relativeSize.x*(float)mapSize.x), (int)(relativeSize.y*(float)mapSize.y)));
}

sf::Vector2f Character::getRelativePosition() const
{
	return m_relativePosition;
}

sf::Vector2f Character::getRelativeSize() const
{
	return m_relativeSize;
}

sf::Vector2f Character::getRelCenter() const
{
	return sf::Vector2f(m_relativePosition.x + m_relativeSize.x/2, m_relativePosition.y + m_relativeSize.y / 2);
}

bool Character::isPointInMyRArea(const sf::Vector2f& resPoint) const
{
	return getRBounds().contains(resPoint);
}

sf::FloatRect Character::getRBounds() const
{
	return sf::FloatRect(m_relativePosition, m_relativeSize);
}

string Character::toString() const
{
	return "Character: cell=" + m_myCell.toString() + ", drawPriority=" + std::to_string(m_drawPriority) + ", " + AnimationView::toString();
}

void Character::updateRelPosSize()
{
	setRelativeSize(m_relativeSize);
	setRelativePosition(m_relativePosition);	
}

bool Character::isNoSet() const
{
	return ((m_relativeSize.x == 0) && (m_relativeSize.y == 0));
}

bool Character::isShowInMap() const
{
	return m_showInMap;
}

LevelScreen& Character::getLevelScreen()
{
	return m_levelScreen;
}

Cell Character::getCell() const
{
	return m_myCell;
}

void Character::checkCollisions()
{
	// get matrix size
	LevelMap::CharsMatrix& charMatrix = getLevelScreen().getLevelMap().getCharsMatrix();
	int rows = charMatrix.getNumOfRows(), cols = charMatrix.getNumOfCols();

	// check collide characters by 9 closed cells
	Cell myCell = getCell();
	Cell checkCell = myCell; // the cell to check collide

	checkCollisionsInCell(checkCell);

	if (myCell.getRowNum() + 1 < rows) {
		checkCell = Cell(myCell.getRowNum() + 1, myCell.getColNum());
		checkCollisionsInCell(checkCell);
	}

	if (myCell.getRowNum() - 1 >= 0) {
		checkCell = Cell(myCell.getRowNum() - 1, myCell.getColNum());
		checkCollisionsInCell(checkCell);
	}

	if (myCell.getColNum() + 1 < cols) {
		checkCell = Cell(myCell.getRowNum(), myCell.getColNum() + 1);
		checkCollisionsInCell(checkCell);
	}

	if (myCell.getColNum() - 1 >= 0) {
		checkCell = Cell(myCell.getRowNum(), myCell.getColNum() - 1);
		checkCollisionsInCell(checkCell);
	}

	if ((myCell.getRowNum() - 1 >= 0) && (myCell.getColNum() - 1 >= 0)) {
		checkCell = Cell(myCell.getRowNum() - 1, myCell.getColNum() - 1);
		checkCollisionsInCell(checkCell);
	}

	if ((myCell.getRowNum() + 1 < rows) && (myCell.getColNum() + 1 < cols)) {
		checkCell = Cell(myCell.getRowNum() + 1, myCell.getColNum() + 1);
		checkCollisionsInCell(checkCell);
	}

	if ((myCell.getRowNum() - 1 >= 0) && (myCell.getColNum() + 1 < cols)) {
		checkCell = Cell(myCell.getRowNum() - 1, myCell.getColNum() + 1);
		checkCollisionsInCell(checkCell);
	}

	if ((myCell.getRowNum() + 1 < rows) && (myCell.getColNum() - 1 >= 0)) {
		checkCell = Cell(myCell.getRowNum() + 1, myCell.getColNum() - 1);
		checkCollisionsInCell(checkCell);
	}
}

sf::Vector2f Character::getStartRelPos() const
{
	return m_startRelPos;
}

void Character::draw()
{
	if (!m_showInMap)
		m_showInMap = true;

	AnimationView::draw();
}

void Character::updateCharCell(bool firstTime)
{	
	// get character matrix
	LevelMap::CharsMatrix& charMatrix = m_levelScreen.getLevelMap().getCharsMatrix();

	// calculate new cell
	sf::Vector2f relCenter = getRelCenter();
	Cell newCell = Utilities::calcCellByPosition(m_levelScreen, relCenter);

	// if cell changed
	if ((m_myCell != newCell)|| firstTime) {
		if (!firstTime) {
			// remove character from matrix
			getLevelScreen().getLevelMap().getCharsMatrix().getCellData(m_myCell).remove(this);
		}

		// add new cell of my in matrix
		charMatrix.getCellData(newCell).push_front(this);

		// update my cell
		m_myCell = newCell;
	}
}

void Character::init()
{
	updateCharCell(true);
	updateRelPosSize();
}

void Character::checkCollisionsInCell(const Cell& cell)
{
	// get characters in cell
	std::list<Character*>& charsInCell = getLevelScreen().getLevelMap().getCharsMatrix().getCellData(cell);
	for (std::list<Character*>::iterator it = charsInCell.begin(); it != charsInCell.end(); ++it) {
		Character& character = (*(*it));
		// if character it not me
		if (&character != this) {
			// check if character collide me
			if (isCollidedWithAnother(character)) {
				// call collide event
				onCollide(character);
			}
		}
	}
}
