//---- include section ------
#include "GameController.h"
#include "LevelFileParser.h"
#include "Player.h"
#include "Wall.h"
#include "Gift.h"
#include "Guard.h"
#include "ExitDoor.h"
#include "Rock.h"
#include "StupidGuard.h"
#include "SmartGuard.h"
#include "Utilities.h"
#include "MainScreen.h"
#include "WinScreen.h"
#include "GameOverScreen.h"
#include "Resources.h"

GameController::GameController()
{
	Resources::loadResources();
}

void GameController::run()
{
	// load music
	sf::Music music;
	music.openFromFile("sounds/game_music.ogg");
	music.setLoop(true);
	music.play();

	// create window 
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Bomberman", sf::Style::Fullscreen);

	// load icon
	window.setIcon(Resources::Images::BombermanIcon.getSize().x, Resources::Images::BombermanIcon.getSize().y,
		Resources::Images::BombermanIcon.getPixelsPtr());

	// run main screen
	runMainScreen(window);

	music.stop();
}

void GameController::runLevelScreen(sf::RenderWindow& window)
{
	// read number of levels
	LevelFileParser lfp;
	int numOfLevels = lfp.getNumOfLevels();

	// create level screen
	LevelScreen levelScreen(window);
	levelScreen.makeRootView();

	bool flagExit = false;

	// set first level
	levelScreen.getGameMenu().getNumLevelView().setNumOfLevel(0);

	while (true) {
		int currentLevel = levelScreen.getGameMenu().getNumLevelView().getNumOfLevel();
		if (currentLevel < numOfLevels) {
			LevelFinishType finishType = runLevel(levelScreen, currentLevel);
			switch (finishType)
			{
				case LevelFinishType::EXIT: {
					return;
				} break;
				case LevelFinishType::GOTO_NEXT: {
					levelScreen.getGameMenu().getNumLevelView()++;	
				} break;
				case LevelFinishType::RELOAD: {
					if (levelScreen.getGameMenu().getLifeview().hasNoLife()) {
						runGameOverScreen(levelScreen.getWindow());
						return;
					}
				} break;
			}
		}
		else {
			// win the game
			runWinScreen(window, levelScreen.getGameMenu().getScoreView().getNumOfScore());
			return;
		}
	}
}

void GameController::runGameOverScreen(sf::RenderWindow& window)
{
	// exit flag
	bool flagExit = false;

	// create main screen
	GameOverScreen gameOverScreen(window);
	gameOverScreen.makeRootView();

	// listen to click events
	gameOverScreen.getBackToMainButton().addClickListener(View::ClickHandler::Listener([&flagExit](View& view) {
		flagExit = true;
	}));

	while (!flagExit)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gameOverScreen.handleEvent(event);
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)))
				return;
		}

		window.clear();
		gameOverScreen.draw();
		window.display();
	}
}

GameController::LevelFinishType GameController::runLevel(LevelScreen& levelScreen, int numOfLevel)
{
	LevelFinishType finishType = LevelFinishType::NONE;

	// load level
	int timeLimit = loadLevel(levelScreen, numOfLevel);

	// listen to restart button
	levelScreen.getGameMenu().getRestartButton().setClickListener(View::ClickHandler::Listener([&levelScreen, &finishType](View& view) {
		levelScreen.getGameMenu().getLifeview()--;
		finishType = GameController::LevelFinishType::RELOAD;
	}));

	// handle time left
	if (levelScreen.isUseTimeLeft()) {
		if (levelScreen.isUseTimeLeft()) {
			levelScreen.getGameMenu().getTimeLeftView().start(timeLimit, [this, &levelScreen, &finishType]() {
				levelScreen.getGameMenu().getLifeview()--;
				finishType = GameController::LevelFinishType::RELOAD;
			});
		}
	}

	// get window
	sf::RenderWindow& window = levelScreen.getWindow();

	// get character list
	CharacterList& charList = levelScreen.getLevelMap().getCharacterList();

	// find player
	Player& player = levelScreen.getLevelMap().getPlayer();

	// listen to end level event
	player.setOnEndLevelListener([this, &levelScreen, &finishType]() {
		// add score
		levelScreen.getGameMenu().getScoreView() += levelScreen.getLevelMap().getNumOfGuards() * 20;
		//  go to next level
		finishType = GameController::LevelFinishType::GOTO_NEXT;
		// play win sound
		m_gameSounds.setBuffer(Resources::Sounds::Win);
		m_gameSounds.play();
	});

	// listen to die event
	bool playerAlreadyDie = false;
	bool flagReloadPositions = false;
	player.setOnDieListener([this, &levelScreen, &finishType, &flagReloadPositions, &playerAlreadyDie]() {
		if (!playerAlreadyDie) {
			playerAlreadyDie = true;
			// decrease life
			LifeView& lifeView = levelScreen.getGameMenu().getLifeview();
			lifeView--;

			if (lifeView.hasNoLife()) {
				finishType = GameController::LevelFinishType::RELOAD; // game over
			}
			else {
				// reload positions
				flagReloadPositions = true;
				// play lose sound
				this->m_gameSounds.setBuffer(Resources::Sounds::RobotDie);
				this->m_gameSounds.play();
			}
		}	
	});

	// run level screen
	while (finishType == LevelFinishType::NONE)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			levelScreen.handleEvent(event);
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))) {
				finishType = LevelFinishType::EXIT;
			}
			else if (event.type == sf::Event::KeyPressed) {
				player.handleKeyPressed(event.key.code);
			}
			else if (event.type == sf::Event::KeyReleased) {
				player.handleKeyReleased(event.key.code);
			}
		}

		// handle characters requests
		levelScreen.getLevelMap().getCharacterList().handleRequests();

		// check collides
		charList.forEach([this, &levelScreen](Character& character) {
			character.checkCollisions();
		});

		// check if player already die
		if (playerAlreadyDie)
			playerAlreadyDie = false;

		// check reload positions
		if (flagReloadPositions) {
			levelScreen.getLevelMap().reloadStartRelPos();
			flagReloadPositions = false;
		}

		window.clear();
		levelScreen.draw();
		window.display();
	}

	return finishType;
}

int GameController::loadLevel(LevelScreen& levelScreen, int numOfLevel)
{
	// clear last level
	levelScreen.clear();

	// load level from file
	LevelFileParser lfp;
	LevelFileParser::FileContent levelFileContent;
	lfp.loadLevel(levelFileContent, numOfLevel);

	// update number of level
	levelScreen.getGameMenu().getNumLevelView().setNumOfLevel(numOfLevel);

	// allowed gifts
	short allowedGifts = Gift::GiftType::LIFE | Gift::GiftType::SCORE | Gift::GiftType::SPEED;

	// metadata of map
	bool useBombs, useTimeLimit;
	useBombs = (levelFileContent.numBombs != LevelFileParser::NOT_USE_BOMBS_LIMIT);
	useTimeLimit = (levelFileContent.numOfTime != LevelFileParser::NOT_USE_BOMBS_LIMIT);
	levelScreen.setUseBombs(useBombs);
	levelScreen.setUseTimeLeft(useTimeLimit);
	if (useBombs) {
		levelScreen.getGameMenu().getBombsView().setNumOfBombs(levelFileContent.numBombs);
		allowedGifts |= Gift::GiftType::BOMB;
	}
	//convert from seconds to milliseconds
	if (useTimeLimit) {
		levelFileContent.numOfTime *= 1000;
		allowedGifts |= Gift::GiftType::TIME;
	}
		

	
	// make relative size of character
	sf::Vector2f StaticCharRelSize(1.f / (float)levelFileContent.map.getNumOfCols(), 1.f / (float)levelFileContent.map.getNumOfRows());
	sf::Vector2f DynamicCharRelSize(0.75f / (float)levelFileContent.map.getNumOfCols(), 0.75f / (float)levelFileContent.map.getNumOfRows());

	// create characters
	levelScreen.getLevelMap().getCharsMatrix().resize(levelFileContent.map.getNumOfRows(), levelFileContent.map.getNumOfCols());
	CharacterList& charList = levelScreen.getLevelMap().getCharacterList();
	int numOfGuards = 0;
	for (int row = 0; row < levelFileContent.map.getNumOfRows(); row++)
	{
		for (int col = 0; col < levelFileContent.map.getNumOfCols(); col++)
		{
			Cell cell(row, col);
			char ch = levelFileContent.map.getCellData(cell);
			switch (ch)
			{
			case Player::PLAYER_SHAPE: {
				Player player(levelScreen.getWindow(), levelScreen, cell, DynamicCharRelSize);
				charList.addCharacterFirst(player);
			} break;
			case Wall::WALL_SHAPE: {
				Wall wall(levelScreen.getWindow(), levelScreen, cell, StaticCharRelSize);
				charList.addCharacterFirst(wall);
			} break;
			case Rock::ROCK_SHAPE: {
				Rock rock(levelScreen.getWindow(), levelScreen, cell, StaticCharRelSize);
				charList.addCharacterFirst(rock);
			} break;
			case Guard::GUARD_SHAPE: {
				// set guard type
				Guard::GuardType guardType = (levelFileContent.guardType == LevelFileParser::RANDOM_GUARD_TYPE) ? Guard::randGuardType()
					                           : static_cast<Guard::GuardType>(levelFileContent.guardType);
				if (guardType == Guard::GuardType::SMART) {
					SmartGuard guard(levelScreen.getWindow(), levelScreen, cell, DynamicCharRelSize);
					charList.addCharacterFirst(guard);
				}
				else {
					StupidGuard guard(levelScreen.getWindow(), levelScreen, cell, DynamicCharRelSize);
					charList.addCharacterFirst(guard);
				}
				numOfGuards++;
			} break;
			case Gift::GIFT_SHAPE: {
				Gift gift(levelScreen.getWindow(), levelScreen, cell, StaticCharRelSize, Gift::randGiftType(allowedGifts));
				charList.addCharacterFirst(gift);
			} break;
			case Gift::GIFT_UNDER_ROCK_SHAPE: {
				Gift gift(levelScreen.getWindow(), levelScreen, cell, StaticCharRelSize, Gift::randGiftType(allowedGifts));
				Rock rock(levelScreen.getWindow(), levelScreen, cell, StaticCharRelSize);
				charList.addCharacterFirst(gift);
				charList.addCharacterFirst(rock);
			} break;
			case ExitDoor::EXIT_DOOR_SHAPE: {
				ExitDoor exitDoor(levelScreen.getWindow(), levelScreen, cell, StaticCharRelSize);
				charList.addCharacterFirst(exitDoor);
			} break;
			case LevelFileParser::EMPTY_SHAPE: {
				// Do nothing
			} break;
			default:
				throw string("Cannot parse the symbol " + string(1, ch));
			}
		}
	}

	// update matrix and list
	charList.sort();

	// make the map in the level map
	levelScreen.getLevelMap().makeMap(numOfGuards);

	return levelFileContent.numOfTime;
}

void GameController::runMainScreen(sf::RenderWindow& window)
{
	// finish game flag
	bool finishFlag = false;

	// create main screen
	MainScreen mainScreen(window);
	mainScreen.makeRootView();

	// listen to click events
	mainScreen.getStartButton().addClickListener(View::ClickHandler::Listener([this, &window](View& view) {
		this->runLevelScreen(window);
	}));
	mainScreen.getExitButton().addClickListener(View::ClickHandler::Listener([this, &window, &finishFlag](View& view) {
		finishFlag = true;
	}));
	

	// run window
	while (window.isOpen())
	{
		if (finishFlag)
			break;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)))
				window.close();
			mainScreen.handleEvent(event);
		}

		window.clear();
		mainScreen.draw();
		window.display();
	}
}

void GameController::runWinScreen(sf::RenderWindow& window, int numOfScore)
{
	bool flagExit = false;

	WinScreen winScreen(window, numOfScore);
	winScreen.makeRootView();

	// listen to button event
	winScreen.getBackButton().addClickListener(View::ClickHandler::Listener([&flagExit](View& view) {
		flagExit = true;
	}));

	while (!flagExit)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			winScreen.handleEvent(event);
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)))
				return;
		}

		window.clear();
		winScreen.draw();
		window.display();
	}
}
