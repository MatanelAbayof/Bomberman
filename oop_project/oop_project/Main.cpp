//------ for SFML library ------------------------------
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib, "sfml-audio.lib" )
#else
#error "Unrecognized configuration!"
#endif

//-------------- include section --------------
#define NOMINMAX    // prevent errors with windows.h
#include <windows.h>
#include <iostream>
#include <time.h>
#include "GameController.h"

//-------------- using section ----------------
using std::cerr;
using std::endl;

//--------------- main ------------------------
int main()
{
	// set seed
	srand((unsigned int) time(NULL));

	// hide console
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	try {
		// start the game
		GameController gameController;
		gameController.run();
	}
	catch (string errorMessage) { // Oh No! error...
		// show console
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
		// print error
		cerr << "Error: " << errorMessage << endl;
		system("pause");
	}
	return EXIT_SUCCESS;
}