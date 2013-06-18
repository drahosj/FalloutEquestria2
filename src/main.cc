/*
 ============================================================================
 Name        : FalloutEquestria2.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include <SDL/SDL.h>
#include "Game.h"
#include "Room.h"

using namespace std;

int main() {
	cout << "Initializing SDL" << endl;
	foe::Game *game;

	game = new foe::Game();
	game->doMainLoop();
	cout << "Exiting..." << endl;

	delete game;
	return 0;
}

void WinMain() { //fuck this shit
	main();
}
