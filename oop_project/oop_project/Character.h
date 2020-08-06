#pragma once
//---- include section ------
#include <string>
#include "AnimationView.h"
#include "Cell.h"
class LevelScreen;
class Guard;
class Player;
class Wall;
class Bomb;
class Rock;
class Gift;
class ExitDoor;
class BlowingUpBomb;

//---- using section --------
using std::string;

/*
 * Character class
 */
class Character :
	public AnimationView
{
public:
	// minimum draw priority
	static const int MINIMUM_PRIORITY = 0;
	// destructor
	virtual ~Character();
	// copy constructor
	Character(Character& anotherCharacter);
	// kill my self
	void killMySelf();
	// get draw priority
	int getDrawPriority() const;
	// set cell location
	void setCellLocation(const Cell& cell);
	// check if character is collided with another character
	bool isCollidedWithAnother(const Character& anotherCharacter) const;
	// set relative position in level map
	void setRelativePosition(const sf::Vector2f& relativePosition);
	// set relative size in level map
	void setRelativeSize(const sf::Vector2f& relativeSize);
	// get relative position in level map
	sf::Vector2f getRelativePosition() const;
	// get relative size in level map
	sf::Vector2f getRelativeSize() const;
	// get relative center
	sf::Vector2f getRelCenter() const;
	// check if point in my relative area
	bool isPointInMyRArea(const sf::Vector2f& resPoint) const;
	// get Relative bounds
	sf::FloatRect getRBounds() const;
	// convert to string
	virtual string toString() const override;
	// update relative position and size when size changed
	void updateRelPosSize();
	// get cell
	Cell getCell() const;
	// check collisions in character in level map (this will call onCollide event)
	void checkCollisions();
	// get start relative position
	sf::Vector2f getStartRelPos() const;
	// draw
	virtual void draw() override;
	// make unique ptr
	virtual std::unique_ptr<Character> clone() = 0;
	// collide events
	virtual void onCollide(Character& character) = 0;
	virtual void onCollide(Guard& character) = 0;
	virtual void onCollide(Player& character) = 0;
	virtual void onCollide(Wall& character) = 0;
	virtual void onCollide(Bomb& character) = 0;
	virtual void onCollide(Rock& character) = 0;
	virtual void onCollide(ExitDoor& character) = 0;
	virtual void onCollide(Gift& character) = 0;
	virtual void onCollide(BlowingUpBomb& character) = 0;
protected:
	// constructor
	Character(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority = MINIMUM_PRIORITY,
		      const sf::Vector2f& relPos = sf::Vector2f(0,0), const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	Character(sf::RenderWindow& window, LevelScreen& levelScreen, int drawPriority = MINIMUM_PRIORITY,
		const Cell& cell = Cell(0, 0), const sf::Vector2f& relSize = sf::Vector2f(0, 0));
	// check if view not set already
	virtual bool isNoSet() const override;
	// check if character is show in map
	bool isShowInMap() const;
	// get level screen
	LevelScreen& getLevelScreen();
	// redeclaring scope of base class functions in protected section of derived class
	using AnimationView::addImage;
	using AnimationView::setImages;
	using AnimationView::setTextures;
	using AnimationView::setImage;
	using AnimationView::setAnimationFrequency;
private:
	// draw priority
	int m_drawPriority;
	// relative position and size in level map
	sf::Vector2f m_relativePosition, m_relativeSize;
	// level screen
	LevelScreen& m_levelScreen;
	// my cell in cahracter matrix
	Cell m_myCell;
	// start relative position
	const sf::Vector2f m_startRelPos;
	// flag if character show in map
	bool m_showInMap;
	// update character cell in matrix
	void updateCharCell(bool firstTime);
	// init
	void init();
	// check collisions in cell (this will call onCollide event)
	void checkCollisionsInCell(const Cell& cell);
};

