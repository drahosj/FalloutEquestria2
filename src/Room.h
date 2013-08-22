/*
 * Room.h
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

#ifndef ROOM_H_
#define ROOM_H_

#include <SDL/SDL.h>
#include <vector>
#include <string>
#include <list>

namespace foe {

class Tile;
class Game;
class Entity;


class Room {
public:
	Room(Game *, unsigned int);
	virtual ~Room();
	void drawTile(int, int);
	void drawAllTiles();
	void drawSurface();
	void drawEntity(Entity *);
	void drawAllEntities();
	std::list<Tile *> * findPath(Tile *, Tile *);
	Entity * getEntity(unsigned long);
	void redrawAll();

	SDL_Surface *surface;

	std::list<Entity *> entities;
	Tile ***tiles;
	unsigned long int uid;
	unsigned int tid;
	int width, height, pixelHeight, pixelWidth;
	Game *game;
	std::vector<std::string> *map;
	std::vector<Tile *> transitions;
private:
	void createTiles();
	Tile * pathSelectNext();
	void pathClearValues();
	void pathExamineNeighbors(Tile *);
	std::list<Entity *>::iterator findEntity(std::list<Entity *>::iterator current, unsigned long);
};

} /* namespace foe */
#endif /* ROOM_H_ */
