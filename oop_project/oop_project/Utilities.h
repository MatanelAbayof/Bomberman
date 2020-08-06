#pragma once
//---- include section ------
#include <string>
#include "Player.h"
#include "LevelMap.h"

//---- using section ----------------
using std::string;

// consts
const float EPSILON = 0.1f; // for compare float points

/*
 * Utilites namespace
 */
namespace Utilities {
	// find player in level screen
	Player& findPlayer(LevelMap& levelMap);
	// calculate cell by relative position
	Cell calcCellByPosition(LevelScreen& levelScreen, const sf::Vector2f& rPos);
	// calculate relative position by cell
	sf::Vector2f calcPositionByCell(LevelScreen& levelScreen, const Cell& cell);
	// check if view with position and size in level bounds (relative data)
	bool inLevelBounds(const sf::Vector2f& rPos, const sf::Vector2f& rSize);
	// get relative center of cell
	sf::Vector2f getRelCenterCell(LevelScreen& levelScreen, const Cell& cell);
	// compare relative points
	bool isEquals(const sf::Vector2f& rPoint1, const sf::Vector2f& rPoint2);
}
