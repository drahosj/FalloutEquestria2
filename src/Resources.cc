/*
 * Resources.cc
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

#include "Resources.h"

namespace foe {

Resources::Resources() {
	loadTiles();
}

Resources::~Resources() {
	// TODO Auto-generated destructor stub
}

void Resources::loadTiles() {
	tile_sprites[0x0] = loadImage("resources/textures/tiles/0000_concrete_0.png");
	tile_sprites[0x1] = loadImage("resources/textures/tiles/0001_concrete_1.png");
	tile_sprites[0x9] = loadImage("resources/textures/tiles/0009_concrete_dark_0.png");
	tile_sprites[0xa] = loadImage("resources/textures/tiles/000a_concrete__dark_1.png");
}

SDL_Surface  * Resources::loadImage(char *name) {
	SDL_Surface *tempImage = 0;
	SDL_Surface *optimizedImage = 0;
	tempImage = IMG_Load(name);
	optimizedImage = SDL_DisplayFormat(tempImage);
	SDL_FreeSurface(tempImage);
	return optimizedImage;
}

SDL_Surface * Resources::getTileSprite(unsigned int id) {
	return tile_sprites[id];
}

} /* namespace foe */
