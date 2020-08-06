#pragma once
//---- include section ------
#include "Guard.h"
#include <string>
#include "Matrix.h"

//---- using section --------
using std::string;

/*
 * SmartGuard class
 */
class SmartGuard :
	public Guard
{
public:
	// BFS cell (=vertex) info
	struct CellInfo
	{
		bool visit;
		Cell myCell, prevCell;
		int distance;
		// infinity distance
		static const int INF_DISTANCE = -1;
	};
	// constructors
	SmartGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const sf::Vector2f& relPos = sf::Vector2f(0, 0),
		       const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	SmartGuard(sf::RenderWindow& window, LevelScreen& levelScreen, const Cell& cell = Cell(0, 0), 
		       const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// copy constructor
	SmartGuard(SmartGuard& samrtGuard);
	// draw
	virtual void draw();
	// play
	virtual void play() override;
	// convert to string
	virtual string toString() const override;
	// make unique ptr
	virtual std::unique_ptr<Character> clone() override;
private:
	// navigate mode of smart guard
	enum NavigateMode {
		RANDOM, PATH
	};
	// default speed
	const float DEFAULT_SPEED = 2.f;
	// path to player
	std::vector<Cell> m_path;
	// navigate mode
	NavigateMode m_navigateMode;
	// index in path
	int m_pathIndex;
	// timer of path
	Timer m_pathTimer;
	// init
	void init();
	// calculate path to player
	void calcPath();
	// build visit matrix
	void buildVisitMatrix(Matrix<CellInfo>& visitMatrix);
	// do BFS algorithm. each cell have maximum of 4 connected cells
	void doBFS(Matrix<CellInfo>& visitMatrix);
};


