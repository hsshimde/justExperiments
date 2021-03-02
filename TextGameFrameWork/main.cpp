
#include "Game.h"


int main()
{
	using namespace game;
	// Use olcConsoleGameEngine derived app
	Game game;

	game.ConstructConsole(160, 100, 8, 8);
	game.Start();

	// Create a console with resolution 160x100 characters
	// Each character occupies 8x8 pixels
	//game.ConstructConsole(160, 100, 8, 8);

	//// Start the engine!
	//game.Start();


	return 0;
}