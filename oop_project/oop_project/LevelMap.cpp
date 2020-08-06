//---- include section ------
#include "LevelMap.h"
#include "Utilities.h"
#include "Bomb.h"
#include "BlowingUpBomb.h"

LevelMap::LevelMap(sf::RenderWindow& window, int numOfRows, int numOfCols)
	: View(window), m_charsMatrix(numOfRows, numOfCols), m_player(nullptr)
{
	init();
}

CharacterList& LevelMap::getCharacterList()
{
	return m_characters;
}

LevelMap::CharsMatrix& LevelMap::getCharsMatrix()
{
	return m_charsMatrix;
}

void LevelMap::clear()
{
	m_characters.clear();
	m_charsMatrix.clear();
}

void LevelMap::draw()
{
	View::draw();

	if (isShow()) {
		m_characters.forEach([](Character& character) {
			character.draw();
		});
	}	
}

Player& LevelMap::getPlayer()
{
	if (m_player == nullptr)
		throw string("Map isn't ready");
	return *m_player;
}

int LevelMap::getNumOfGuards()
{
	return m_numOfGuards;
}

void LevelMap::reloadStartRelPos()
{
	getCharacterList().forEach([this](Character& character) {
		// check if is bomb
		if (Bomb* bomb = dynamic_cast<Bomb*>(&character)) {
			this->getCharacterList().requestRemoveCharacter(*bomb);
		}
		// check if is blowing up bomb
		 if (BlowingUpBomb* bub = dynamic_cast<BlowingUpBomb*>(&character)) {
			this->getCharacterList().requestRemoveCharacter(*bub);
		}
		// set start position
		character.setRelativePosition(character.getStartRelPos());
	});
}

void LevelMap::makeMap(int numOfGuards)
{
	m_player = &Utilities::findPlayer(*this);
	m_numOfGuards = numOfGuards;
}

string LevelMap::toString() const
{
	return "LevelMap: " + View::toString();
}

void LevelMap::handleClickEvent(int mouseX, int mouseY)
{
	View::handleClickEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		m_characters.forEach([mouseX, mouseY](Character& character) {
			character.handleClickEvent(mouseX, mouseY);
		});
	}
}

void LevelMap::handleEnterEvent(int mouseX, int mouseY)
{
	View::handleEnterEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		m_characters.forEach([mouseX, mouseY](Character& character) {
			character.handleEnterEvent(mouseX, mouseY);
		});
	}
}

void LevelMap::handleLeaveEvent(int mouseX, int mouseY)
{
	View::handleLeaveEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		m_characters.forEach([mouseX, mouseY](Character& character) {
			character.handleLeaveEvent(mouseX, mouseY);
		});
	}
}

void LevelMap::updateComponents()
{
	View::updateComponents();

	m_characters.forEach([](Character& character) {
		character.updateRelPosSize();
	});
}

void LevelMap::init()
{
	getBackground().setColor(sf::Color(255, 255, 230));
	disable(); // disable all mouse events
}
