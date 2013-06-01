/*
 * Room.cc
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

#include "Room.h"
#include "Game.h"
#include "Tile.h"
#include <SDL/SDL.h>
#include <string>
#include "Entity.h"
#include <iostream>
#include <algorithm>

namespace foe {

Room::Room(Game *game, unsigned int id): game(game), tid(id) {
	uid = game->getNextUid();
	SDL_PixelFormat *format = game->screen->format;

	map = game->resources->getMap(tid);
	width = atoi((*map)[0].c_str());
	height = atoi((*map)[0].c_str());

	pixelWidth = Tile::TILE_SIZE * width;
	pixelHeight = Tile::TILE_SIZE * height;

	surface = SDL_CreateRGBSurface(game->screen->flags, pixelWidth, pixelHeight, format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);
	createTiles();

	entities = new std::list<Entity *>;
	Entity *testEntity = new Entity(2, 2, 0, this);
	game->playerUid = testEntity->uid;

	entities->push_back(testEntity);
	testEntity = getEntity(game->playerUid);

}

Room::~Room() {
	for (int i  = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			delete tiles[i][j];
			//TODO: Delete All Entities then delete entities!
			SDL_FreeSurface(surface);
			delete map;
		}
	}
}

void Room::createTiles() {
	tiles = new Tile**[width];

	for (int i  = 0; i < width; i++) {
		tiles[i] = new Tile*[height];
	}

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if ((*map)[j+2].c_str()[i] == 'F')
				tiles[i][j] = new Tile(i, j, Tile::Types::CONCRETE_0, this);
			else if ((*map)[j+2].c_str()[i] == 'W')
				tiles[i][j] = new Tile(i, j, Tile::Types::WALL_0, this);
		}
	}
}

void Room::drawSurface() {
	SDL_Rect srcrect;
	srcrect.h = pixelWidth;
	srcrect.w = pixelHeight;
	srcrect.x = 0;
	srcrect.y = 0;
	SDL_Rect dstrect;
	dstrect.h = pixelWidth;
	dstrect.w = pixelHeight;
	dstrect.x = 25;
	dstrect.y = 25;

	SDL_BlitSurface(surface, &srcrect, game->screen, &dstrect);
}

void Room::drawAllTiles() {
	for (int i  = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			drawTile(i, j);
		}
	}
}

void Room::drawTile(int x, int y) {
	SDL_Rect srcrect;
	srcrect.h = Tile::TILE_SIZE;
	srcrect.w = Tile::TILE_SIZE;
	srcrect.x = 0;
	srcrect.y = 0;
	SDL_Rect dstrect;
	dstrect.h = Tile::TILE_SIZE;
	dstrect.w = Tile::TILE_SIZE;
	dstrect.x = Tile::TILE_SIZE * x;
	dstrect.y = Tile::TILE_SIZE * y;
	SDL_BlitSurface(tiles[x][y]->sprite, &srcrect, surface, &dstrect);
}

Entity * Room::getEntity(unsigned long uid) {
	std::list<Entity *>::iterator target;

	target = findEntity(entities->begin(), uid);

	return *target;
}

std::list<Entity *>::iterator Room::findEntity(std::list<Entity *>::iterator current, unsigned long targetUid) {
	if ((*current)->uid == targetUid)
		return current;
	else
		return findEntity(++current, targetUid);
}

void Room::drawEntity(Entity *entity) {
	SDL_Rect srcrect;
	srcrect.h = Tile::TILE_SIZE; //TODO: Entity sizes...
	srcrect.w = Tile::TILE_SIZE;
	srcrect.x = 0;
	srcrect.y = 0;
	SDL_Rect dstrect;
	dstrect.h = Tile::TILE_SIZE;
	dstrect.w = Tile::TILE_SIZE;
	dstrect.x = Tile::TILE_SIZE * entity->x;
	dstrect.y = Tile::TILE_SIZE * entity->y;
	SDL_BlitSurface(entity->sprite, &srcrect, surface, &dstrect);
}

void Room::drawAllEntities() {
	std::list<Entity *>::iterator current = entities->begin();
	do {
		drawEntity(*current);
		current++;
	} while (current != entities->end());
}
} /* namespace foe */
