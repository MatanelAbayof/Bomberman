#pragma once
//---- include section ------
#include <list>
#include "Character.h"
#include <functional>
#include <queue>

/*
 * CharacterList
*/
class CharacterList
{
public:
	// character list
	typedef std::list<std::unique_ptr<Character>> CharsList;
	// constructor
	CharacterList() = default;
	// add character
	void addCharacter(Character& character);
	// get character (use for test only, because runtime is O(n))
	Character* getCharacter(int index);
	// remove character
	void removeCharacter(Character& character);
	// add character - without sorting!
	void addCharacterFirst(Character& character);
	// sort character list
	void sort();
	// clear list
	void clear();
	// request to add character
	void requestAddCharacter(Character& character);
	// request to remove character
	void requestRemoveCharacter(Character& character);
	// handle requests (add and remove characters)
	void handleRequests();
	// get list
	CharsList& getList();
	// for each
	void forEach(std::function<void(Character&)> onGetCharacter);
	// get num of character
	int getNumOfCharacter() const;
	// convert to string
	string toString();
private:
	// list of characters
	CharsList m_charcters;
	// add characters queue
	std::queue<std::unique_ptr<Character>> m_addCharsRequests;
	// remove characters queue
	std::queue<Character*> m_removeCharsRequests;
	// handle add requests
	void handleAddRequests();
	// handle remove requests
	void handleRemoveRequests();
};