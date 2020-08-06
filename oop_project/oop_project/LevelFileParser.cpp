//---- include section ------
#include "LevelFileParser.h"
#include <fstream>

void LevelFileParser::loadLevel(FileContent& fileContent, int numOfLevel)
{
	if(numOfLevel < 0) 
		throw string("Number of level must be bigger or equals to zero (=" + std::to_string(numOfLevel) + ")");

	// open file
	std::ifstream fp(NAME_OF_FILE);

	// check if can't open the file
	if (!fp.is_open())
		throw string("Cannot open file (=" + string(NAME_OF_FILE) + ")");

	// run on file until the wanted level
	for (int i = 0; i < numOfLevel; i++)
	{
		// skip to next level
		continueToNextLevel(fp);
	}

	// read metadata
	int numOfRows, numOfCols;
	fp >> fileContent.numBombs >> fileContent.numOfTime >> fileContent.guardType >> numOfRows >> numOfCols;

	// set map size
	fileContent.map.resize(numOfRows, numOfCols);

	// set map data
	fp.get(); // for new line
	for (int row = 0; row < numOfRows; row++)
	{
		for (int col = 0; col < numOfCols; col++)
		{
			Cell cell(row, col);
			char ch = fp.get();
			fileContent.map.setCellData(cell, ch);
		}
		// for new line
		fp.get();
	}

	// close the file
	fp.close();
}

int LevelFileParser::getNumOfLevels()
{
	std::ifstream fp(NAME_OF_FILE);
	// can't open the file
	if (!fp.is_open())
		throw string("Cannot open file (= " + string(NAME_OF_FILE) + ")");

	// check if file is empty
	if (fp.peek() == std::ifstream::traits_type::eof())
		return 0;

	int countLevel = 0;
	// run on file and count level
	while (!fp.eof())
	{
		// read one level
		continueToNextLevel(fp);
		countLevel++;
	}
	fp.close();

	return countLevel;
}

void LevelFileParser::continueToNextLevel(std::ifstream& fp)
{
	// read from file until end of level
	while (true)
	{
		if (fp.eof()) // end of file
			break;
		string str;
		// read line
		std::getline(fp, str);
		// end of level
		if (str.empty())
			break;
	}
}
