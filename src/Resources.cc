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
#include "Game.h"
#include "Entity.h"
#include "Character.h"

namespace foe {

Resources::Resources(Game *game) : game(game){
}

void Resources::loadAll() {
	loadTiles();
	loadMaps();
	loadEntities();
	loadUiElements();
}

Resources::~Resources() {
	// TODO Auto-generated destructor stub
}

SDL_Surface * Resources::getUiElement(unsigned int id) {
	return ui_elements[id];
}

void Resources::loadTiles() {
	tile_sprites[0x0] = loadImage("res/textures/tiles/0000_concrete_0.png");
	tile_sprites[0x1] = loadImage("res/textures/tiles/0001_concrete_1.png");
	tile_sprites[0x9] = loadImage("res/textures/tiles/0009_concrete_dark_0.png");
	tile_sprites[0xa] = loadImage("res/textures/tiles/000a_concrete_dark_1.png");
	tile_sprites[0x10] = loadImage("res/textures/tiles/0010_wall_0.png");
}


void Resources::loadUiElements() {
	ui_elements[0x0] = loadImage("res/textures/ui/0000_walkpath.png");
	ui_elements[0x1] = loadImage("res/textures/ui/0001_walk_red.png");
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
	while(std::getline(mapfile, s)) {
		input->push_back(s);
	}
	mapfile.close();
	return input;
}

std::vector<std::string> * Resources::getMap(unsigned int id) {
	return maps[id];
}

Character * Resources::characterFromRaw(std::string charName) {
	int str, per, end, cha, intel, agi, lck;

	std::ifstream rawfile;
	std::string s;
	std::string value;
	std::string::iterator iter;
	std::string fileName = "res/raws/character/";
	fileName+= charName;
	fileName+= ".raw";

	rawfile.open(fileName.c_str());

	std::getline(rawfile, s); //throw away first line

	std::getline(rawfile, s);
	str = parseRawString(s);

	std::getline(rawfile, s);
	per = parseRawString(s);

	std::getline(rawfile, s);
	end = parseRawString(s);

	std::getline(rawfile, s);
	cha = parseRawString(s);

	std::getline(rawfile, s);
	intel = parseRawString(s);

	std::getline(rawfile, s);
	agi = parseRawString(s);

	std::getline(rawfile, s);
	lck = parseRawString(s);


	rawfile.close();

	return new Character(str, per, end, cha, intel, agi, lck, game);
}

int Resources::parseRawString(std::string str) {
	std::string value;
	std::string::iterator iter;

	iter = str.begin();
	while ((iter != str.end()) && (*iter != '=')) {
		iter++;
	}
	while (iter != str.end()) {
		iter++;
		value += *iter;
	}
	return atoi(value.c_str());
}

void Resources::loadMaps() {
	maps[0x1] = loadMap("res/maps/01.mpf");

}
} /* namespace foe */
