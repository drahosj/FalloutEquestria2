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

namespace foe {

class Game {
public:
	Game();
	virtual ~Game();
	unsigned long int getNextUid();

	Resources * resources;

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	const int SCREEN_BPP;

	SDL_Surface *screen;
private:
	unsigned long int nextUid;
};

} /* namespace foe */
#endif /* GAME_H_ */
