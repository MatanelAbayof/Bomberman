//---- include section ------
#include "Resources.h"
#include "Utilities.h"

// init resources
sf::Font Resources::Fonts::Arial, Resources::Fonts::ARBD;
sf::Texture Resources::Images::Rock, Resources::Images::Wall, 
	        Resources::Images::ExitDoor, Resources::Images::Life,
	        Resources::Images::Bomb, Resources::Images::Coin,
	        Resources::Images::Watch, Resources::Images::BombermanBackground,
	        Resources::Images::GameOverBackground, Resources::Images::WinBackground;
sf::Image Resources::Images::BombermanIcon;
std::vector<sf::Texture> Resources::Animations::Bomb(3), Resources::Animations::Explosion(15), 
                         Resources::Animations::GuardTopDir(14), Resources::Animations::GuardDownDir(14), 
						 Resources::Animations::GuardRightDir(14), Resources::Animations::GuardLeftDir(14),
						 Resources::Animations::OpenGift(4), Resources::Animations::RobotUpDir(6),
						 Resources::Animations::RobotDownDir(5), Resources::Animations::RobotRightDir(7),
						 Resources::Animations::RobotLeftDir(7), Resources::Animations::GuardDie(6);
sf::SoundBuffer Resources::Sounds::Explosion, Resources::Sounds::BtClick, Resources::Sounds::BtHover,
				Resources::Sounds::RobotDie, Resources::Sounds::AnimalDie, Resources::Sounds::Win,
	            Resources::Sounds::BombTick, Resources::Sounds::GiftOpen;


void Resources::loadResources()
{
	Fonts::loadFonts();
	Images::loadImages();
	Animations::loadAnimations();
	Sounds::loadSounds();
}

void Resources::Images::loadImages()
{
	// images dir relative path
	string imagesDirPath = "images";

	// load images
	Rock.loadFromFile(imagesDirPath + "\\rock.png");
	Wall.loadFromFile(imagesDirPath + "\\wall.png");
	ExitDoor.loadFromFile(imagesDirPath + "\\exit_door.png");
	BombermanIcon.loadFromFile(imagesDirPath + "\\bomberman-icon.png");
	Life.loadFromFile(imagesDirPath + "\\life.png");
	Bomb.loadFromFile(imagesDirPath + "\\Bomb.png");
	Coin.loadFromFile(imagesDirPath + "\\coin.png");
	Watch.loadFromFile(imagesDirPath + "\\watch.png");
	BombermanBackground.loadFromFile(imagesDirPath + "\\bomberman_background.png");
	WinBackground.loadFromFile(imagesDirPath + "\\win_background.png");
	GameOverBackground.loadFromFile(imagesDirPath + "\\sad_robot.jpg");
}

void Resources::Fonts::loadFonts()
{
	// fonts dir relative path
	string fontsDirPath = "fonts";

	// load fonts
	Arial.loadFromFile(fontsDirPath + "\\arial.ttf");
	ARBD.loadFromFile(fontsDirPath + "\\ARLRDBD.TTF");
}

void Resources::Animations::loadAnimations()
{
	// animations dir relative path
	string animDirPath = "animations";

	// load bomb
	for (size_t i = 0; i < Bomb.size(); i++) {
		Bomb[i].loadFromFile(animDirPath + "\\Bomb\\Bomb" + std::to_string(i + 1) + ".png");
	}

	// load explosion
	for (size_t i = 0; i < Explosion.size(); i++) {
		Explosion[i].loadFromFile(animDirPath + "\\Explosion\\ex_" + std::to_string(i + 1) + ".gif");
	}

	// load guard
	for (size_t i = 0; i < GuardLeftDir.size(); i++) {
		GuardLeftDir[i].loadFromFile(animDirPath + "\\Guard\\left\\g_" + std::to_string(i + 1) + ".gif");
	}
	for (size_t i = 0; i < GuardRightDir.size(); i++) {
		GuardRightDir[i].loadFromFile(animDirPath + "\\Guard\\right\\g_" + std::to_string(i + 1) + ".gif");
	}
	for (size_t i = 0; i < GuardTopDir.size(); i++) {
		GuardTopDir[i].loadFromFile(animDirPath + "\\Guard\\top\\g_" + std::to_string(i + 1) + ".gif");
	}
	for (size_t i = 0; i < GuardDownDir.size(); i++) {
		GuardDownDir[i].loadFromFile(animDirPath + "\\Guard\\down\\g_" + std::to_string(i + 1) + ".gif");
	}
	for (size_t i = 0; i < GuardDie.size(); i++) {
		GuardDie[i].loadFromFile(animDirPath + "\\Guard\\die\\g_" + std::to_string(i + 1) + ".gif");
	}

	// load gift
	for (size_t i = 0; i < OpenGift.size(); i++) {
		OpenGift[i].loadFromFile(animDirPath + "\\Gift\\gift_" + std::to_string(i) + ".gif");
	}

	// load robot
	for (size_t i = 0; i < RobotUpDir.size(); i++) {
		RobotUpDir[i].loadFromFile(animDirPath + "\\Robot\\up\\up_" + std::to_string(i + 1) + ".gif");
		RobotUpDir[i].setSmooth(true);
	}
	for (size_t i = 0; i < RobotDownDir.size(); i++) {
		RobotDownDir[i].loadFromFile(animDirPath + "\\Robot\\down\\down_" + std::to_string(i + 1) + ".gif");
		RobotDownDir[i].setSmooth(true);
	}
	for (size_t i = 0; i < RobotLeftDir.size(); i++) {
		RobotLeftDir[i].loadFromFile(animDirPath + "\\Robot\\left\\left_" + std::to_string(i + 1) + ".gif");
		RobotLeftDir[i].setSmooth(true);
	}
	for (size_t i = 0; i < RobotRightDir.size(); i++) {
		RobotRightDir[i].loadFromFile(animDirPath + "\\Robot\\right\\right_" + std::to_string(i + 1) + ".gif");
		RobotRightDir[i].setSmooth(true);
	}
}

void Resources::Sounds::loadSounds()
{
	// sounds dir relative path
	string soundsDirPath = "sounds";

	Explosion.loadFromFile(soundsDirPath + "\\explosion.ogg");
	BtClick.loadFromFile(soundsDirPath + "\\bt_click.ogg");
	BtHover.loadFromFile(soundsDirPath + "\\bt_hover.ogg");
	RobotDie.loadFromFile(soundsDirPath + "\\robot_die.ogg");
	AnimalDie.loadFromFile(soundsDirPath + "\\animal_die.ogg");
	Win.loadFromFile(soundsDirPath + "\\win.ogg");
	BombTick.loadFromFile(soundsDirPath + "\\bomb_tick.ogg");
	GiftOpen.loadFromFile(soundsDirPath + "\\chest_open.ogg");
}
