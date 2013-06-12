/*
 * Game.h
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

#ifndef GAME_H_
#define GAME_H_

#include <SDL/SDL.h>
#include "Resources.h"
#include <list>


namespace foe {

class Room;
class Tile;

class Game {
public:
	Game();
	virtual ~Game();
	unsigned long getNextUid();
	void doMainLoop();
	void redrawUI();


	unsigned long playerUid;

	Resources * resources;
	Room * currentRoom;
	int cursorMode;

	std::list<Tile *> * path;

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	const int SCREEN_BPP;

	const static int CURSOR_NORMAL = 0;
	const static int CURSOR_MOVE = 1;

	SDL_Surface *screen;
	SDL_Surface *ui;
private:
	unsigned long nextUid;
};

} /* namespace foe */
#endif /* GAME_H_ */
