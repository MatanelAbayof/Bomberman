#pragma once
//---- include section ------
#include "View.h"
#include "CharacterList.h"
#include "Matrix.h"
#include <list>
#include "Player.h"

/*
 * LevelMap class
 */
class LevelMap :
	public View
{
public:
	// typedef
	typedef Matrix<std::list<Character*>> CharsMatrix;
	// constructor
	LevelMap(sf::RenderWindow& window, int numOfRows = 0, int numOfCols = 0);
	// get character list
	CharacterList& getCharacterList();
	// get character matrix
	CharsMatrix& getCharsMatrix();
	// clear
	void clear();
	// draw
	virtual void draw() override;
	// get player
	Player& getPlayer();
	//get num of guards
	int getNumOfGuards();
	// reload start relative positions of all cahracters
	void reloadStartRelPos();
	// make map
	void makeMap(int numOfGuards);
	// convert to string
	virtual string toString() const override;
protected:
	// handle click event
	virtual void handleClickEvent(int mouseX, int mouseY);
	// handle enter event
	virtual void handleEnterEvent(int mouseX, int mouseY);
	// handle leave event
	virtual void handleLeaveEvent(int mouseX, int mouseY);
	// update components
	virtual void updateComponents() override;
private:
	// characters matrix
	CharsMatrix m_charsMatrix;
	// characters
	CharacterList m_characters;
	// player
	Player* m_player;
	//num of guards
	int m_numOfGuards;
	// init
	void init();
};

