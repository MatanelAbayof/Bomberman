#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//---- using section ----------------
using std::string;

/*
 * Resources namespace
 * all members here are global
 */
namespace Resources {

	// images
	namespace Images {
		extern sf::Texture Rock, Wall, ExitDoor, Life, Bomb, Coin, Watch, BombermanBackground, GameOverBackground, WinBackground;
		extern sf::Image BombermanIcon;
		
		// load images recources
		void loadImages();
	}

	// animations
	namespace Animations {
		extern std::vector<sf::Texture> Bomb, Explosion, GuardTopDir, GuardDownDir, GuardRightDir, 
			      GuardLeftDir, GuardDie, OpenGift, RobotUpDir, RobotDownDir, RobotRightDir, RobotLeftDir;

		// load animations recources
		void loadAnimations();
	}
	
	// fonts 
	namespace Fonts {
		extern sf::Font Arial, ARBD;

		// load fonts recources
		void loadFonts();
	}

	// sounds 
	namespace Sounds {
		extern sf::SoundBuffer Explosion, BtHover, BtClick, RobotDie, 
			                   AnimalDie, Win, BombTick, GiftOpen;

		// load fonts recources
		void loadSounds();
	}

	// load all recources
	void loadResources();
}
