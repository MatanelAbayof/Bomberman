//---- include section ------
#include "Matrix.h"
#include "Character.h"
#include "SmartGuard.h"
#include <list>

template<class T>
Matrix<T>::Matrix(int numOfRows, int numOfCols)
{
	resize(numOfRows, numOfCols);
}

template<class T>
void Matrix<T>::resize(int numOfRows, int numOfCols)
{
	if (!isLegalSize(numOfRows, numOfCols))
		throw string("Ilegal size of matrix: rows=" + std::to_string(numOfRows) + ", cols=" + std::to_string(numOfCols));
	m_numOfRows = numOfRows;
	m_numOfCols = numOfCols;
	// delete last matrix
	m_data.clear();
	// set matrix size
	m_data.resize(numOfRows);
	for (int rowNum = 0; rowNum < m_numOfRows; rowNum++) {
		m_data[rowNum].resize(numOfCols);
	}
}

template<class T>
void Matrix<T>::setCellData(const Cell& cell, T& data)
{
	if (!isCellExists(cell))
		throw string("Cell " + cell.toString() + " don't exists in matrix");
	m_data[cell.getRowNum()][cell.getColNum()] = data;
}

template<class T>
int Matrix<T>::getNumOfRows() const
{
	return m_numOfRows;
}

template<class T>
int Matrix<T>::getNumOfCols() const
{
	return m_numOfCols;
}

template<class T>
void Matrix<T>::clear()
{
	m_data.clear();
}

template<class T>
T& Matrix<T>::getCellData(const Cell& cell)
{
	if (!isCellExists(cell))
		throw string("Cell " + cell.toString() + " don't exists in matrix");
	return m_data[cell.getRowNum()][cell.getColNum()];
}

template<class T>
void Matrix<T>::forEach(std::function<void(const Cell&, T&)> onGetCellData)
{
	for (int rowNum = 0; rowNum < m_numOfRows; rowNum++) {
		for (int colNum = 0; colNum < m_numOfCols; colNum++) {
			Cell cell(rowNum, colNum);
		 	 onGetCellData(cell, getCellData(cell));
		}
	}
}

template<class T>
string Matrix<T>::toString() const
{
	return "Matrix: rows=" + std::to_string(m_numOfRows) + ", cols=" + std::to_string(m_numOfCols);
}

template<class T>
bool Matrix<T>::isCellExists(const Cell& cell) const
{
	return ((cell.getRowNum() < m_numOfRows) && (cell.getColNum() < m_numOfCols));
}

template<class T>
bool Matrix<T>::isLegalSize(int numOfRows, int numOfCols) const
{
	return ((numOfRows >= 0) && (numOfCols >= 0));
}




// Explicit instantiation, because the compiler is stupid!
template class Matrix<std::list<Character*>>;
template class Matrix<char>;
template class Matrix<SmartGuard::CellInfo>;