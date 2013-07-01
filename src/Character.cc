/*
 * Character.cc
 *
 *  Created on: Jun 1, 2013
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

#include "Character.h"
#include "Game.h"
#include "Entity.h"
#include "Room.h"

namespace foe {

Character::Character(int s, int p, int e, int c, int i, int a, int l, Game *game) {
	baseSpecial.strength = s;
	baseSpecial.perception = p;
	baseSpecial.endurance = e;
	baseSpecial.charisma = c;
	baseSpecial.intelligence = i;
	baseSpecial.agility = a;
	baseSpecial.luck = l;

	entity = 0;

	uid = game->getNextUid();
	refreshStats();
}


void Character::enterRoom(Room *room, int x, int y, unsigned int entityType) {
	if (entity != 0) {
		delete entity;
	}

	entity = new Entity(x, y, entityType, room);
}
void Character::refreshStats() {
	derivedSpecial = baseSpecial; //meh, works for now

//	walkDistance = (derivedSpecial.endurance + derivedSpecial.agility * 2) + 1 / 2; //+1 = shitty round up
	int end, agi;
	end = derivedSpecial.endurance;
	agi = derivedSpecial.agility;

	walkDistance = (((end + (2 * agi) + 1) / 2) * 3) / 5;

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

} /* namespace foe */
