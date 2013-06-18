/*
 * Game.cc
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

#include "Game.h"
#include "Room.h"
#include "Entity.h"
#include "Tile.h"
#include "Character.h"
#include <list>

namespace foe {

Game::Game() : SCREEN_WIDTH(640), SCREEN_HEIGHT(640), SCREEN_BPP(32), nextUid(0), cursorMode(0), movePath(0){
	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	resources.loadAll();

	playerUid = 0;

	Room *testroom = new Room(this, 1);

	Character *tc = new Character(5,5,5,5,5,5,5, this);

	characters.push_back(tc);

	tc->entity = new Entity(2, 2, Entity::PLAYER, testroom);

	testroom->entities.push_back(tc->entity);

	testroom->drawAllTiles();
	testroom->drawAllEntities();

	currentRoom = testroom;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

unsigned long Game::getNextUid() {
	return ++nextUid;
}

void Game::doMainLoop() {
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case (SDL_QUIT):
				quit = true;
				break;
			case (SDL_MOUSEBUTTONDOWN):
				if ((event.button.button == SDL_BUTTON_LEFT) && (cursorMode == CURSOR_MOVE)) {
					std::list<Tile *>::iterator iter = movePath->begin();
					int dist = 0;
					while ((iter != movePath->end()) && (dist <= (*characters.begin())->walkDistance)) {
						iter++;
						dist++;
					}
					iter--;

					(*characters.begin())->entity->x = (*iter)->x;
					(*characters.begin())->entity->y = (*iter)->y;
					cursorMode = CURSOR_NORMAL;
					delete movePath;
					movePath = 0;
					redrawUI();
				}
				if ((event.button.button == SDL_BUTTON_RIGHT) && (cursorMode == CURSOR_MOVE)) {
					cursorMode = CURSOR_NORMAL;
					delete movePath;
					movePath = 0;
					redrawUI();
				}
				break;
			case (SDL_MOUSEMOTION):
				if (cursorMode == CURSOR_MOVE) {
					if (event.motion.x < 25)
						break;
					if (event.motion.y < 25)
						break;
					if (event.motion.x >= currentRoom->width * Tile::TILE_SIZE + 25)
						break;
					if (event.motion.y >= currentRoom->height * Tile::TILE_SIZE + 25)
						break;

					Tile *start, *end;
					Entity *player = (*characters.begin())->entity;

					start = currentRoom->tiles[player->x][player->y];
					end = currentRoom->tiles[(event.motion.x - 25) / Tile::TILE_SIZE][(event.motion.y - 25) / Tile::TILE_SIZE];

					delete movePath;
					movePath = currentRoom->findPath(start, end);
				}
				break;
			case (SDL_KEYDOWN):
				if (event.key.keysym.sym == SDLK_m) {
					if (cursorMode == CURSOR_NORMAL) {
						Tile *start, *end;
						int x, y;
						SDL_GetMouseState(&x, &y);

						Character *player = *characters.begin();

						start = currentRoom->tiles[player->entity->x][player->entity->y];
						end = currentRoom->tiles[(x - 25) / Tile::TILE_SIZE][(y - 25) / Tile::TILE_SIZE];
						delete movePath;
						movePath = currentRoom->findPath(start, end);
						cursorMode = CURSOR_MOVE;
					}
					else {
						cursorMode = CURSOR_NORMAL;
						delete movePath;
						movePath = 0;

					}
				}
				break;
			}
		}
		currentRoom->redrawAll();
		redrawUI();
		SDL_Flip(screen);
	}
}

void Game::redrawUI() {
	currentRoom->drawSurface();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = Tile::TILE_SIZE;
	rect.w = Tile::TILE_SIZE;

	int dist = 0;
	if (movePath != 0) {
		std::list<Tile *>::iterator iter = movePath->begin();
		do {
			rect.x = (*iter)->x * Tile::TILE_SIZE + 25;
			rect.y = (*iter)->y * Tile::TILE_SIZE + 25;
			if (dist <= (*characters.begin())->walkDistance)
				SDL_BlitSurface(resources.getUiElement(0x0), NULL, screen, &rect);
			else
				SDL_BlitSurface(resources.getUiElement(0x1), NULL, screen, &rect);
			iter++;
			dist++;
		} while (iter != movePath->end());
		SDL_Flip(screen);
	}
}
} /* namespace foe */
