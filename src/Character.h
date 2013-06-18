/*
 * Character.h
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

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Entity.h"

namespace foe {
class Game;

class Character {
public:
	Character(int, int, int, int, int, int, int, Game *);
	virtual ~Character();
	struct Special {
		int strength;
		int perception;
		int endurance;
		int charisma;
		int intelligence;
		int agility;
		int luck;
	};

	int walkDistance;
	unsigned long int uid;

	Special baseSpecial;
	Special derivedSpecial;
	Entity *entity;

	void refreshStats();
};

} /* namespace foe */
#endif /* CHARACTER_H_ */
