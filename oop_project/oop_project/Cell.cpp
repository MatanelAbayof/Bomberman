//---- include section ------
#include "Cell.h"

Cell::Cell(int rowNum, int colNum) 
{
	setCell(rowNum, colNum);
}

int Cell::getRowNum() const
{
	return m_rowNum;
}

int Cell::getColNum() const
{
	return m_colNum;
}

void Cell::setCell(int rowNum, int colNum)
{
	if (isValidCell(rowNum, colNum))
	{
		m_rowNum = rowNum;
		m_colNum = colNum;
	}
	else
		throw string("Illegal cell: rowNum = " + std::to_string(rowNum) + ", colNum = " + std::to_string(colNum));
}

void Cell::setRowNum(int rowNum)
{
	if (rowNum < 0)
		throw string("Ilegal row number =" + std::to_string(rowNum));
	m_rowNum = rowNum;
}

void Cell::setColNum(int colNum)
{
	if (colNum < 0)
		throw string("Ilegal column number =" + std::to_string(colNum));
	m_colNum = colNum;
}

bool Cell::isValidCell(int rowNum, int colNum)
{
	if ((rowNum < 0) || (colNum < 0))
		return false;
	return true;
}

Cell Cell::getUpCell() const
{
	return Cell(m_rowNum - 1, m_colNum);
}

Cell Cell::getDownCell() const
{
	return Cell(m_rowNum + 1, m_colNum);
}

Cell Cell::getLeftCell() const
{
	return Cell(m_rowNum, m_colNum - 1);
}

Cell Cell::getRightCell() const
{
	return Cell(m_rowNum, m_colNum + 1);
}

string Cell::toString() const
{
	return "Cell: number of row: " + std::to_string(m_rowNum) + ", number of col: " + std::to_string(m_colNum);
}

bool Cell::operator==(const Cell &anotherCell)
{
	return (getRowNum() == anotherCell.getRowNum()) && (getColNum() == anotherCell.getColNum());
}

bool Cell::operator!=(const Cell &anotherCell)
{
	return ((getRowNum() != anotherCell.getRowNum()) || (getColNum() != anotherCell.getColNum()));
}

bool Cell::isAboveThen(const Cell &otherCell) const
{
	return (m_rowNum == otherCell.m_rowNum - 1 && m_colNum == otherCell.m_colNum);
}

bool Cell::isUnderThen(const Cell &otherCell) const
{
	return (m_rowNum == otherCell.m_rowNum + 1 && m_colNum == otherCell.m_colNum);
}

bool Cell::isLeftTo(const Cell &otherCell) const
{
	return (m_rowNum == otherCell.m_rowNum && m_colNum == otherCell.m_colNum - 1);
}

bool Cell::isRightTo(const Cell &otherCell) const
{
	return (m_rowNum == otherCell.m_rowNum && m_colNum == otherCell.m_colNum + 1);
}