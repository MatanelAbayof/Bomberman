//---- include section ------
#include "Utilities.h"
#include <windows.h>
#include "CharacterList.h"
#include "LevelScreen.h"
#include <cmath>


Player& Utilities::findPlayer(LevelMap& levelMap)
{
	CharacterList::CharsList& characters = levelMap.getCharacterList().getList();
	for (CharacterList::CharsList::iterator it = characters.begin(); it != characters.end(); ++it) {
		if (Player* player = dynamic_cast<Player*>((*it).get())) {
			return *player;
		}
	}
	throw string("Not found player!");	
}

sf::Vector2f Utilities::calcPositionByCell(LevelScreen& levelScreen, const Cell& cell)
{
	// get character matrix
	LevelMap::CharsMatrix& charMatrix = levelScreen.getLevelMap().getCharsMatrix();
	return sf::Vector2f((float)cell.getColNum() / (float)charMatrix.getNumOfCols(), 
		   (float)cell.getRowNum()/(float)charMatrix.getNumOfRows());
}

bool Utilities::inLevelBounds(const sf::Vector2f& rPos, const sf::Vector2f& rSize)
{
	return ((rPos.x >= 0.f) && (rPos.y >= 0.f) && (rPos.x + rSize.x <= 1.f)
			&& (rPos.y + rSize.y <= 1.f));
}

sf::Vector2f Utilities::getRelCenterCell(LevelScreen& levelScreen, const Cell& cell)
{
	// get character matrix
	LevelMap::CharsMatrix& charMatrix = levelScreen.getLevelMap().getCharsMatrix();
	sf::Vector2f cellPos = calcPositionByCell(levelScreen, cell);
	return sf::Vector2f(cellPos.x + (1.f/(float)charMatrix.getNumOfCols())/2.f, cellPos.y + (1.f / (float)charMatrix.getNumOfRows())/2.f);
}

bool Utilities::isEquals(const sf::Vector2f & rPoint1, const sf::Vector2f & rPoint2)
{
	return (abs(rPoint1.x - rPoint2.x) < EPSILON) && (abs(rPoint1.y - rPoint2.y) < EPSILON);
}

Cell Utilities::calcCellByPosition(LevelScreen& levelScreen, const sf::Vector2f& rPos)
{
	// get character matrix
	LevelMap::CharsMatrix& charMatrix = levelScreen.getLevelMap().getCharsMatrix();

	Cell cell((int)(rPos.y*(float)charMatrix.getNumOfRows()), (int)(rPos.x*(float)charMatrix.getNumOfCols()));
	if (cell.getRowNum() + 1 > charMatrix.getNumOfRows())
		cell.setRowNum(charMatrix.getNumOfRows() - 1);
	if (cell.getColNum() + 1 > charMatrix.getNumOfCols())
		cell.setColNum(charMatrix.getNumOfCols() - 1);
	return cell;
}
