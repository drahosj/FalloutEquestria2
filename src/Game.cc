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
#include <list>

namespace foe {

Game::Game() : SCREEN_WIDTH(640), SCREEN_HEIGHT(480), SCREEN_BPP(32), nextUid(0), cursorMode(0), path(0){
	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	resources = new Resources();
	playerUid = 0;

	Room *testroom = new Room(this, 1);

	Entity *testEntity = new Entity(2, 2, 0, testroom);
	playerUid = testEntity->uid;

	SDL_PixelFormat fmt = *screen->format;
	ui = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
	SDL_SetColorKey(ui, SDL_SRCCOLORKEY, SDL_MapRGB(ui->format, 0, 0, 0));


	SDL_FillRect(ui, NULL, SDL_MapRGBA(&fmt, 0, 0, 0, 0));



	testroom->entities->push_back(testEntity);

	testroom->drawAllTiles();
	testroom->drawAllEntities();
	//testroom->drawEntity(testroom->getEntity(playerUid));
	testroom->drawSurface();
	SDL_Flip(screen);

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
				SDL_FillRect(ui, NULL, SDL_MapRGBA(screen->format, 0, 0, 0, 0)); //Blank UI
				if ((event.button.button == SDL_BUTTON_LEFT) && (cursorMode == CURSOR_MOVE)) {
					currentRoom->getEntity(playerUid)->x = (event.button.x - 25) / 25;
					currentRoom->getEntity(playerUid)->y = (event.button.y - 25) / 25;
					cursorMode = CURSOR_NORMAL;
				}
				if ((event.button.button == SDL_BUTTON_RIGHT) && (cursorMode == CURSOR_MOVE)) {
					cursorMode = CURSOR_NORMAL;
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
					Entity *player = currentRoom->getEntity(playerUid);

					start = currentRoom->tiles[player->x][player->y];
					end = currentRoom->tiles[(event.motion.x - 25) / Tile::TILE_SIZE][(event.motion.y - 25) / Tile::TILE_SIZE];

//					start = currentRoom->tiles[1][1];
//					end = currentRoom->tiles[4][3];
					delete path;
					path = currentRoom->findPath(start, end);

					SDL_FillRect(ui, NULL, SDL_MapRGBA(screen->format, 0, 0, 0, 0)); //Blank UI

					SDL_Rect rect;
					rect.x = 0;
					rect.y = 0;
					rect.h = Tile::TILE_SIZE;
					rect.w = Tile::TILE_SIZE;

					std::list<Tile *>::iterator iter = path->end();
					do {
						iter--;
						rect.x = (*iter)->x * Tile::TILE_SIZE + 25;
						rect.y = (*iter)->y * Tile::TILE_SIZE + 25;
						SDL_FillRect(ui, &rect, SDL_MapRGBA(screen->format, 0, 255, 0, 80));
					} while (iter != path->begin());
				}
				break;
			case (SDL_KEYDOWN):
				if (event.key.keysym.sym == SDLK_m) {
					if (cursorMode == CURSOR_NORMAL)
						cursorMode = CURSOR_MOVE;
					else
						cursorMode = CURSOR_NORMAL;
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
	SDL_BlitSurface(ui, NULL, screen, NULL);
}
} /* namespace foe */
