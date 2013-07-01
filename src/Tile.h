/*
 * Tile.h
 *
 *  Created on: May 25, 2013
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

#ifndef TILE_H_
#define TILE_H_

#include <SDL/SDL.h>

namespace foe {
class Room;

class Tile {
public:
	Tile(int, int, unsigned int, Room *);
	virtual ~Tile();

	const static int TILE_SIZE = 25;
	const static int DIST_MAX = 9999;

	Room *room;
	int x, y;
	unsigned int tid;
	unsigned long int uid;
	SDL_Surface *sprite;
	bool pathable;
	Tile * travelTarget;

	int distance; //Pathfinding values; volatile between pathing operations...
	bool visited;
	Tile *predecessor;

	class Types {
	public:
		#include "TileTypes.h"
		};
};

} /* namespace foe */
#endif /* TILE_H_ */
