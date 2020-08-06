#pragma once
//---- include section ------
#include <string>
#include <functional>
#include <vector>
#include "Cell.h"

//---- using section --------
using std::string;

/*
 * generic matrix class
 */
template <class T>
class Matrix
{
public:
	// constructor
	Matrix(int numOfRows = 0, int numOfCols = 0);
	// set size
	void resize(int numOfRows, int numOfCols);
	// set cell data
	void setCellData(const Cell& cell, T& data);
	// get number of rowss
	int getNumOfRows() const;
	// get number of columns
	int getNumOfCols() const;
	// clear
	void clear();
	// get cell data
	T& getCellData(const Cell& cell);
	// for each all cells
	void forEach(std::function<void(const Cell&, T&)> onGetData);
	// convert to string
	virtual string toString() const;
	// check if cell exists
	bool isCellExists(const Cell& cell) const;
private:
	// matrix data
	std::vector<std::vector<T>> m_data;
	// matrix dimensions
	int m_numOfRows, m_numOfCols;
	// check legal dimensions
	bool isLegalSize(int numOfRows, int numOfCols) const;
};

