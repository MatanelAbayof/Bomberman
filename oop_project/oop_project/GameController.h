#pragma once
//---- include section ------
#include <string>
#include "LevelScreen.h"
#include "Character.h"

//---- using section --------
using std::string;

/*
 * GameController class
 */
class GameController
{
public:
	// the type of finish the level
	enum LevelFinishType {
		EXIT, RELOAD, GOTO_NEXT, NONE
	};
	// constructor
	GameController();
	// run
	void run();
private:
	// game sounds (like win or die)
	sf::Sound m_gameSounds;
	// run main screen
	void runMainScreen(sf::RenderWindow& window);
	// run win screen
	void runWinScreen(sf::RenderWindow& window, int numOfScore);
	// run level screen
	void runLevelScreen(sf::RenderWindow& window);
	// run game over screen
	void runGameOverScreen(sf::RenderWindow& window);
	// run level
	LevelFinishType runLevel(LevelScreen& levelScreen, int numOfLevel);
	// load level from file. return level time
	int loadLevel(LevelScreen& levelScreen, int numOfLevel);
};

