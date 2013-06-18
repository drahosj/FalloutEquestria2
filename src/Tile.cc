/*
 * Tile.cc
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

#include "Tile.h"
#include "Room.h"
#include "Game.h"
#include "TileTypes.h"

namespace foe {

Tile::Tile(int x, int y, unsigned int id, Room *room) : x(x), y(y), tid(id), pathable(false), room(room), predecessor(0), visited(false), distance(DIST_MAX){
	uid = room->game->getNextUid();
	sprite = room->game->resources->getTileSprite(tid);
	switch (tid) {
	case (Types::CONCRETE_0): //Add all PATHABLE=TRUE Types here
	case (Types::CONCRETE_1):
	case (Types::CONCRETE_DARK_0):
	case (Types::CONCRETE_DARK_1):
		pathable = true;
		break;
	}
}

Tile::~Tile() {
}

} /* namespace foe */
