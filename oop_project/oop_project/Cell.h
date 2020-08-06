#pragma once
//---- include section ------
#include <string>

//---- using section --------
using std::string;

/*
 * Cell class
 */
class Cell
{
public:
	// default row number and column number of cell
	static const int DEFAULT_ROW_NUM = 0, DEFAULT_COL_NUM = 0;
	// constructor
	Cell(int rowNum = DEFAULT_ROW_NUM, int colNum = DEFAULT_COL_NUM);
	//get num of row
	int getRowNum() const;
	//get num of column
	int getColNum() const;
    //set new cell
	void setCell(int rowNum, int colNum);
	// set row number
	void setRowNum(int rowNum);
	// set column number
	void setColNum(int colNum);
	// get up cell
	Cell getUpCell() const;
	//get down cell
	Cell getDownCell() const;
	//get left cell
	Cell getLeftCell() const;
	//get right cell
	Cell getRightCell() const;
	//check if cell is above the other
	bool isAboveThen(const Cell &otherCell) const;
	//check if cell is under the other
	bool isUnderThen(const Cell &otherCell) const;
	//check if cell is left to the other
	bool isLeftTo(const Cell &otherCell) const;
	//check if cell is right to the other
	bool isRightTo(const Cell &otherCell) const;
	//check if the cell is valid
	static bool isValidCell(int rowNum, int colNum);
	// convert to string
	virtual string toString() const;
	// overloading compare operator
	bool operator == (const Cell &anotherCell);
	// overloading compare operator
	bool operator != (const Cell &anotherCell);
private:
	// number of row
	int m_rowNum;
	// number of column
	int m_colNum;
};
