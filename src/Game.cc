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
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Exceptions.h"

namespace foe {

Game::Game() : nextUid(0), cursorMode(0), movePath(0), resources(this){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	/*try {
	resources.loadAll();
	} catch (loadImageError& e) {
		std::cout << "Shit broke. Expect segfaults." << std::endl;
		std:: cout<< "Exception: " << e.what() << std::endl;;
		throw e;
	}*/ //Boilerplate catching of errors

	resources.loadAll();

	playerUid = 0;


	Character *tc = resources.characterFromRaw("player"); //create a character, characters exist within games (the character gets its game from the resources)
	characters.push_back(tc); // add the character to the game's list of characters

	//Room *testroom = new Room(this, 1); //create a room. Rooms exist within games
	Room *testroom = resources.roomFromRaw("01"); // generate room from raw

	tc->enterRoom(testroom, 2, 2, Entity::PLAYER); //Create an entity. Entities only exist within rooms, but belong to entities or other whatsits

	currentRoom = testroom;

//	Room *otherroom = new Room(this, 2);
	Room *otherroom = resources.roomFromRaw("02");

	//hardcoded travel target
	//testroom->tiles[1][1]->travelTarget = otherroom->tiles[8][1];

	testroom->transitions[0]->travelTarget = otherroom->transitions[0]; //Raw-generated transition start
	testroom->transitions[1]->travelTarget = otherroom->transitions[1]; //Raw-generated transition start
	testroom->transitions[2]->travelTarget = otherroom->transitions[2]; //Raw-generated transition start

	otherroom->transitions[0]->travelTarget = testroom->transitions[0]; //Raw-generated transition start
	otherroom->transitions[1]->travelTarget = testroom->transitions[1]; //Raw-generated transition start
	otherroom->transitions[2]->travelTarget = testroom->transitions[2]; //Raw-generated transition start


	//BEGIN SPECIAL PANE GENERATION ---- THIS SHOULD BE SEPARATE //todo separate them
	uiSpecialPane = NULL;
	textColor = {255, 255, 255}; //meh
	textFont = TTF_OpenFont("res/liberation.ttf", 12);
	char  message[500];
	sprintf(message,
			"Strength: %d\n"
			"Perception: %d\n"
			"Endurance: %d\n"
			"Charisma: %d\n"
			"Intelligence: %d\n"
			"Agility: %d\n"
			"Luck: %d\n\n"
			"Press 'm' and left-\n    click to move!\n"
			"Right click to cancel",
			tc->derivedSpecial.strength,
			tc->derivedSpecial.perception,
			tc->derivedSpecial.endurance,
			tc->derivedSpecial.charisma,
			tc->derivedSpecial.intelligence,
			tc->derivedSpecial.agility,
			tc->derivedSpecial.luck);

	std::istringstream msg(message);
	std::string line;
	SDL_PixelFormat *format = screen->format;
	SDL_Surface *tmp = NULL;
	uiSpecialPane = SDL_CreateRGBSurface(screen->flags, 250, 250, format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = uiSpecialPane->w;
	rect.h = 12; //font height
	while (std::getline(msg, line)) {
		tmp = TTF_RenderText_Solid(textFont, line.c_str(), textColor);
		SDL_BlitSurface(tmp, NULL, uiSpecialPane, &rect);
		rect.y += TTF_FontLineSkip(textFont);
	}
	SDL_SetColorKey(uiSpecialPane, SDL_SRCCOLORKEY, SDL_MapRGB(format, 0, 0, 0));
	//THIS NEEDS TO BE SEPARATED!!
}

Game::~Game() {
	delete &logger;
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
			case (SDL_MOUSEBUTTONDOWN): //			=======================MOUSEBUTTONDOWN=================================
				if ((event.button.button == SDL_BUTTON_LEFT) && (cursorMode == CURSOR_MOVE)) {
					std::list<Tile *>::iterator iter = movePath->begin();
					int dist = 0;
					while ((iter != movePath->end()) && (dist <= (*characters.begin())->walkDistance)) {
						iter++;
						dist++;
					}
					iter--;

					if ((*iter)->travelTarget == 0){ //Not a door/transition
						(*characters.begin())->entity->x = (*iter)->x; //MOVE CHARACTER!
						(*characters.begin())->entity->y = (*iter)->y;
					} else if (((*iter)->travelTarget->room == currentRoom) && (*iter == movePath->back())) { //Same room door, lolwut
						(*characters.begin())->entity->x = (*iter)->travelTarget->x;
						(*characters.begin())->entity->y = (*iter)->travelTarget->y;
					} else if (((*iter)->travelTarget->room != currentRoom) && (*iter == movePath->back())) { //Change room
						(*characters.begin())->enterRoom((*iter)->travelTarget->room, (*iter)->travelTarget->x, (*iter)->travelTarget->y, Entity::PLAYER);
						currentRoom = (*iter)->travelTarget->room;
					} else { //Not a door/transition
						(*characters.begin())->entity->x = (*iter)->x; //MOVE CHARACTER!
						(*characters.begin())->entity->y = (*iter)->y;
					}

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
			case (SDL_MOUSEMOTION)://                =========================MOUSEMOTION=====================================
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
			case (SDL_KEYDOWN):// ==================================================KEYDOWN===========================================
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

			rect.x = (*iter)->x * Tile::TILE_SIZE + ROOM_X;
			rect.y = (*iter)->y * Tile::TILE_SIZE + ROOM_Y;
			if (((*(iter))->travelTarget != 0) && (*iter == movePath->back())) //if is a transition and the last part
				SDL_BlitSurface(resources.getUiElement(0x3), NULL, screen, &rect);
			else if (dist <= (*characters.begin())->walkDistance)
				SDL_BlitSurface(resources.getUiElement(0x0), NULL, screen, &rect);
			else
				SDL_BlitSurface(resources.getUiElement(0x1), NULL, screen, &rect);
			iter++;
			dist++;
		} while (iter != movePath->end());
	}


	rect.x = RIGHT_PANE_X; //Draw RIGHT PANE Background
	rect.y = RIGHT_PANE_Y;
	rect.h = 0;
	rect.w = 0;
	SDL_BlitSurface(resources.getUiElement(0x02), NULL, screen, &rect);

	rect.x = RIGHT_PANE_X + SPECIAL_PANE_X; //Draw SPECIAL Pane
	rect.y = RIGHT_PANE_Y + SPECIAL_PANE_Y;
	rect.h = 0;
	rect.w = 0;
	SDL_BlitSurface(uiSpecialPane, NULL, screen, &rect);

	SDL_Flip(screen);
}
} /* namespace foe */
