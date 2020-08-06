#pragma once
//---- include section ------
#include <string>
#include "LevelScreen.h"
#include "Matrix.h"
#include <fstream>

//---- using section --------
using std::string;

/*
 * LevelFileParser class
 */
class LevelFileParser
{
public:
	// guard types
	static const int SMART_GUARD_TYPE = 0;
	static const int STUPID_GUARD_TYPE = 1;
	// not use bombs & time left
	static const int NOT_USE_BOMBS_LIMIT = -1;
	static const int NOT_USE_TIME_LIMIT = -1;
	// create random guards (smart or stupid)
	static const int RANDOM_GUARD_TYPE = -1;
	// empty cell shape
	static const char EMPTY_SHAPE = ' ';
	// file content
	struct FileContent {
		int numBombs, numOfTime, guardType;
		Matrix<char> map;
	};
	// load level
	void loadLevel(FileContent& fileContent, int numOfLevel);
	// get number of levels
	int getNumOfLevels();
private:
	// the name of file
	const char *NAME_OF_FILE = "board.bomb";
	// continue to next level in the file
	void continueToNextLevel(std::ifstream &fp);
};

