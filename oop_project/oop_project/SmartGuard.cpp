//---- include section ------
#include "SmartGuard.h"
#include "LevelScreen.h"
#include <queue>
#include "Utilities.h"
#include "BlowingUpBomb.h"

SmartGuard::SmartGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos,
	                   const sf::Vector2f& relSize)
	: Guard(window, levelScreen, relPos, relSize)
{
	init();
}

SmartGuard::SmartGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell,
	                   const sf::Vector2f& relSize)
	: Guard(window, levelScreen, cell, relSize)
{
	init();
}

SmartGuard::SmartGuard(SmartGuard& smartGuard)
	: Guard(smartGuard)
{
	init();
}

void SmartGuard::draw()
{
	m_pathTimer.checkTimer();
	Guard::draw();
}

void SmartGuard::play()
{
	// get next position
	sf::Vector2f nextPosition = requestNextPosition();
	// check if can move to next position
	if (canMove(nextPosition)) {
		// move
		setRelativePosition(nextPosition);

		// check if navigate mode is by path
		if (m_navigateMode == NavigateMode::PATH) {
			if (!m_path.empty()) {

				// if guard is in player cell
				if (m_pathIndex + 1 > static_cast<int>(m_path.size())) {
					setDirection(DynamicCharacter::Direction::STANDING);
				}
				else {
					// get next cell
					Cell nextCell = m_path[m_path.size() - m_pathIndex - 1];
					// get next cell relative center
					sf::Vector2f relNextCellCenter = Utilities::getRelCenterCell(getLevelScreen(), nextCell);
					// my relative center
					sf::Vector2f myRelCenter = getRelCenter();


					// if come to next cell
					if (m_pathIndex + 1 == m_path.size()) {
						if (getCell() == nextCell)
							m_pathIndex++;
					}
					else {
						if (Utilities::isEquals(myRelCenter, relNextCellCenter))
							m_pathIndex++;
					}
					
					// go to next cell
					if (getCell().isAboveThen(nextCell)) {
						if (getDirection() == DynamicCharacter::Direction::UP) {
							setCellLocation(nextCell);
							setDirection(DynamicCharacter::Direction::STANDING);
						} else
							setDirection(DynamicCharacter::Direction::DOWN);
					}
					else if (getCell().isUnderThen(nextCell)) {
						if (getDirection() == DynamicCharacter::Direction::DOWN) {
							setCellLocation(nextCell);
							setDirection(DynamicCharacter::Direction::STANDING);
						}
						else
							setDirection(DynamicCharacter::Direction::UP);
					}
					else if (getCell().isLeftTo(nextCell)) {
						if (getDirection() == DynamicCharacter::Direction::LEFT) {
							setCellLocation(nextCell);
							setDirection(DynamicCharacter::Direction::STANDING);
						}
						else
							setDirection(DynamicCharacter::Direction::RIGHT);
					}
					else if (getCell().isRightTo(nextCell)) {
						if (getDirection() == DynamicCharacter::Direction::RIGHT) {
							setCellLocation(nextCell);
							setDirection(DynamicCharacter::Direction::STANDING);
						}
						else
							setDirection(DynamicCharacter::Direction::LEFT);
					}
				}
			}
		}	
	}	
	else {	
		// check if navigate mode is by path
		if (m_navigateMode == NavigateMode::PATH) {
			// do smart random direction to next cell
			if (getDirection() == Direction::DOWN || getDirection() == Direction::UP)
				setDirection(getHRandomDirect());
			else if (getDirection() == Direction::LEFT || getDirection() == Direction::RIGHT)
				setDirection(getVRandomDirect());
		}
		else {
			// do random direction
			setDirection(getRandomDirect());
		}
		// change navigate mode to random
		m_navigateMode = RANDOM;
	}	
}

string SmartGuard::toString() const
{
	return string("SmartGuard: " + DynamicCharacter::toString());
}

std::unique_ptr<Character> SmartGuard::clone()
{
	return std::make_unique<SmartGuard>(*this);
}

void SmartGuard::init()
{
	setSpeed(DEFAULT_SPEED);
	setDirection(DynamicCharacter::Direction::STANDING);
	m_navigateMode = NavigateMode::RANDOM;
	m_pathTimer.start(500, [this]() {
		this->calcPath();
	});

	addCollideCharacterType(typeid(BlowingUpBomb).name());
}


void SmartGuard::calcPath()
{
	// reset direction
	setDirection(DynamicCharacter::Direction::STANDING);
	m_path.clear();
	m_pathIndex = 0;

	// get map info
	LevelMap::CharsMatrix& charMat = getLevelScreen().getLevelMap().getCharsMatrix();
	CharacterList::CharsList& charList = getLevelScreen().getLevelMap().getCharacterList().getList();
	Player& player = getLevelScreen().getLevelMap().getPlayer();

	// create visit matrix map
	Matrix<CellInfo> visitMatrix(charMat.getNumOfRows(), charMat.getNumOfCols());
	buildVisitMatrix(visitMatrix);

	// do BFS on visit matrix
	doBFS(visitMatrix);

	// build path
	Cell currCell = player.getCell();
	int dist = visitMatrix.getCellData(currCell).distance;
	while (dist > 0) {
		m_path.push_back(currCell);
		currCell = visitMatrix.getCellData(currCell).prevCell;
		dist--;
	}

	// set new navigate mode
	if (m_path.size() > 0) {
		m_navigateMode = NavigateMode::PATH;
	}
	else {
		m_navigateMode = NavigateMode::RANDOM;
		setDirection(getRandomDirect());
	}
}

void SmartGuard::buildVisitMatrix(Matrix<CellInfo>& visitMatrix)
{
	// get map info
	LevelMap::CharsMatrix& charMat = getLevelScreen().getLevelMap().getCharsMatrix();

	// reset cells and check collide characters
	visitMatrix.forEach([this, &visitMatrix, &charMat](const Cell& cell, CellInfo& cellInfo) {
		visitMatrix.getCellData(cell).myCell = cell;
		visitMatrix.getCellData(cell).distance = CellInfo::INF_DISTANCE;
		visitMatrix.getCellData(cell).visit = false;

		// get characters in cell
		std::list<Character*>& charsInCell = charMat.getCellData(cell);

		// check collide character
		for (std::list<Character*>::iterator it = charsInCell.begin(); it != charsInCell.end(); ++it) {
			Character& character = (*(*it));
			if (this->isCharInMyCollideM(character)) {
				visitMatrix.getCellData(character.getCell()).visit = true;
				break;
			}
		}
	});

	// init me
	visitMatrix.getCellData(getCell()).distance = 0;
	visitMatrix.getCellData(getCell()).visit = true;
}

void SmartGuard::doBFS(Matrix<CellInfo>& visitMatrix)
{
	// get player
	Player& player = getLevelScreen().getLevelMap().getPlayer();

	// applying BFS on matrix cells starting from source (the guard cell)
	std::queue<CellInfo*> q;
	q.push(&visitMatrix.getCellData(getCell()));

	while (!q.empty()) {
		CellInfo* cellInfo = q.front();
		q.pop();

		// destination found (the player cell)
		if (cellInfo->myCell == player.getCell())
			break;

		// moving up 
		if (cellInfo->myCell.getRowNum() - 1 >= 0 && visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum() - 1,
			cellInfo->myCell.getColNum())).visit == false) {
			CellInfo* nextCellInfo = &visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum() - 1,
				cellInfo->myCell.getColNum()));
			nextCellInfo->distance = cellInfo->distance + 1;
			nextCellInfo->visit = true;
			nextCellInfo->prevCell = cellInfo->myCell;
			q.push(nextCellInfo);
		}

		// moving down 
		if (cellInfo->myCell.getRowNum() + 1 < visitMatrix.getNumOfRows() && visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum() + 1,
			cellInfo->myCell.getColNum())).visit == false) {
			CellInfo* nextCellInfo = &visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum() + 1,
				cellInfo->myCell.getColNum()));
			nextCellInfo->distance = cellInfo->distance + 1;
			nextCellInfo->visit = true;
			nextCellInfo->prevCell = cellInfo->myCell;
			q.push(nextCellInfo);
		}

		// moving left 
		if (cellInfo->myCell.getColNum() - 1 >= 0 && visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum(),
			cellInfo->myCell.getColNum() - 1)).visit == false) {
			CellInfo* nextCellInfo = &visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum(),
				cellInfo->myCell.getColNum() - 1));
			nextCellInfo->distance = cellInfo->distance + 1;
			nextCellInfo->visit = true;
			nextCellInfo->prevCell = cellInfo->myCell;
			q.push(nextCellInfo);
		}

		// moving right 
		if (cellInfo->myCell.getColNum() + 1 < visitMatrix.getNumOfCols() && visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum(),
			cellInfo->myCell.getColNum() + 1)).visit == false) {
			CellInfo* nextCellInfo = &visitMatrix.getCellData(Cell(cellInfo->myCell.getRowNum(),
				cellInfo->myCell.getColNum() + 1));
			nextCellInfo->distance = cellInfo->distance + 1;
			nextCellInfo->visit = true;
			nextCellInfo->prevCell = cellInfo->myCell;
			q.push(nextCellInfo);
		}
	}
}
