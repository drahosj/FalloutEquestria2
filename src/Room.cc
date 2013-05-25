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
#include <iostream>

namespace foe {

Room::Room(Game *game, unsigned int id): game(game), tid(id) {
	uid = game->getNextUid();
	SDL_PixelFormat *format = game->screen->format;

	map = game->resources->getMap(tid);
	width = atoi((*map)[0].c_str());
	height = atoi((*map)[0].c_str());

	surface = SDL_CreateRGBSurface(game->screen->flags, 300, 300, format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);
	createTiles();
}

Room::~Room() {
	for (int i  = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			//delete tiles[i][j];
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
	srcrect.h = 300;
	srcrect.w = 300;
	srcrect.x = 0;
	srcrect.y = 0;
	SDL_Rect dstrect;
	dstrect.h = 300;
	dstrect.w = 300;
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
	srcrect.h = 25;
	srcrect.w = 25;
	srcrect.x = 0;
	srcrect.y = 0;
	SDL_Rect dstrect;
	dstrect.h = 25;
	dstrect.w = 25;
	dstrect.x = 25 * x;
	dstrect.y = 25 * y;
	SDL_BlitSurface(tiles[x][y]->sprite, &srcrect, surface, &dstrect);
}

} /* namespace foe */
