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

using namespace std;

int main(void) {
	std::cout << "Initializing SDL" << endl;
	foe::Game *game;

	game = new foe::Game();
	SDL_Delay(1000);
	std::cout << "Exiting..." << endl;
	return 0;
}
