/*
 * Game.cc
 *
 *  Created on: May 24, 2013
 *      Author: jake
 *
 *  Copyright (C) 2013  Jake Drahos
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "Game.h"
#include "Room.h"

namespace foe {

Game::Game() : SCREEN_WIDTH(640), SCREEN_HEIGHT(480), SCREEN_BPP(32), nextUid(0) {
	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	resources = new Resources();

	Room *testroom = new Room(this, 1);
	testroom->drawAllTiles();
	testroom->drawSurface();
	SDL_Flip(screen);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

unsigned long int Game::getNextUid() {
	return ++nextUid;
}

} /* namespace foe */
