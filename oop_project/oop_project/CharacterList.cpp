//---- include section ------
#include "CharacterList.h"

void CharacterList::addCharacter(Character& character)
{
	// if is first character
	if (m_charcters.empty()) {
		addCharacterFirst(character);
		return;
	}

	for (CharsList::iterator it = m_charcters.begin();
		it != m_charcters.end(); ++it)
	{
		if (character.getDrawPriority() < (*it)->getDrawPriority()) {
			m_charcters.insert(it, character.clone());
			return;
		}
	}

	// if is last character
	m_charcters.push_back(character.clone());
}

Character* CharacterList::getCharacter(int index)
{
	CharsList::iterator it = m_charcters.begin();
	std::advance(it, index);
	return (*it).get();
}

void CharacterList::removeCharacter(Character& character)
{
	for (CharsList::iterator it = m_charcters.begin();
		it != m_charcters.end(); ++it)
	{
		if (&character == it->get()) {
			m_charcters.erase(it);
			break;
		}
	}
}

void CharacterList::addCharacterFirst(Character& character)
{
	m_charcters.push_front(character.clone());
}

void CharacterList::sort()
{
	m_charcters.sort([](const std::unique_ptr<Character>& char1, const std::unique_ptr<Character>& char2)
	{
		return (char1->getDrawPriority() < char2->getDrawPriority());
	});
}

void CharacterList::clear()
{
	m_charcters.clear();
}

void CharacterList::requestAddCharacter(Character& character)
{
	m_addCharsRequests.push(character.clone());
}

void CharacterList::requestRemoveCharacter(Character& character)
{
	m_removeCharsRequests.push(&character);
}

void CharacterList::handleRequests()
{
	handleAddRequests();
	handleRemoveRequests();
}

CharacterList::CharsList& CharacterList::getList()
{
	return m_charcters;
}

void CharacterList::forEach(std::function<void(Character&)> onGetCharacter)
{
	for (CharsList::iterator it = m_charcters.begin();
		it != m_charcters.end(); ++it)
	{
		onGetCharacter(*it->get());
	}
}

int CharacterList::getNumOfCharacter() const
{
	return static_cast<int>(m_charcters.size());
}

string CharacterList::toString()
{
	string charsData = "CharacterList: ";
	for (CharsList::iterator it = m_charcters.begin();
		 it != m_charcters.end(); ++it)
	{
		charsData += it->get()->toString() + "\n";
	}
	return charsData;
}

void CharacterList::handleAddRequests()
{
	while (!m_addCharsRequests.empty()) {
		addCharacter(*m_addCharsRequests.front());
		m_addCharsRequests.pop();
	}
}

void CharacterList::handleRemoveRequests()
{
	while (!m_removeCharsRequests.empty()) {
		removeCharacter(*m_removeCharsRequests.front());
		m_removeCharsRequests.pop();
	}
}
