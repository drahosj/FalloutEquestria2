/*
 * Resources.h
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

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include <string>
#include <vector>

namespace foe {

class Character;
class Game;
class Resources {
public:
	Resources(Game *);
	virtual ~Resources();

	SDL_Surface * getTileSprite(unsigned int);
	SDL_Surface * getEntitySprite(unsigned int);
	SDL_Surface * getUiElement(unsigned int);
	std::vector<std::string> * getMap(unsigned int);
	Character * characterFromRaw(std::string);
	void loadAll();
	Game *game;
private:
	std::map<int, SDL_Surface *> tile_sprites;
	std::map<int, std::vector<std::string>*> maps;
	std::map<int, SDL_Surface *> entity_sprites;
	std::map<int, SDL_Surface *> ui_elements;

	void loadTiles();
	int parseRawString(std::string);
	void loadMaps();
	void loadEntities();
	void loadUiElements();
	std::vector<std::string>* loadMap(char *);
	SDL_Surface * loadImage(char*);
};

} /* namespace foe */
#endif /* RESOURCES_H_ */
