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
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

namespace foe {

Resources::Resources() {
	loadTiles();
	loadMaps();
	loadEntities();
}

Resources::~Resources() {
	// TODO Auto-generated destructor stub
}

void Resources::loadTiles() {
	tile_sprites[0x0] = loadImage("res/textures/tiles/0000_concrete_0.png");
	tile_sprites[0x1] = loadImage("res/textures/tiles/0001_concrete_1.png");
	tile_sprites[0x9] = loadImage("res/textures/tiles/0009_concrete_dark_0.png");
	tile_sprites[0xa] = loadImage("res/textures/tiles/000a_concrete_dark_1.png");
	tile_sprites[0x10] = loadImage("res/textures/tiles/0010_wall_0.png");
}

void Resources::loadEntities() {
	entity_sprites[0x0] = loadImage("res/textures/entities/characters/0000_player.png");
}

SDL_Surface  * Resources::loadImage(char *name) {
	SDL_Surface *tempImage = 0;
	SDL_Surface *optimizedImage = 0;
	tempImage = IMG_Load(name);
	optimizedImage = SDL_DisplayFormatAlpha(tempImage);
	SDL_FreeSurface(tempImage);
	return optimizedImage;
}

SDL_Surface * Resources::getTileSprite(unsigned int id) {
	return tile_sprites[id];
}

SDL_Surface * Resources::getEntitySprite(unsigned int id) {
	return entity_sprites[id];
}

std::vector<std::string> * Resources::loadMap(char *name) {
	std::ifstream mapfile;
	std::string s;

	mapfile.open(name);
	std::vector<std::string> *input = new std::vector<std::string>;
	while(mapfile) {
		std::getline(mapfile, s);
		input->push_back(s);
	}
	mapfile.close();
	return input;
}

std::vector<std::string> * Resources::getMap(unsigned int id) {
	return maps[id];
}

void Resources::loadMaps() {
	maps[0x1] = loadMap("res/maps/01.mpf");

}
} /* namespace foe */
