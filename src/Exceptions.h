/*
 * Exceptions.h
 *
 *  Created on: Jul 27, 2013
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

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>
#include <stdexcept>

namespace foe {

class loadImageError : public std::runtime_error {
public:
	loadImageError(std::string message);
};

class loadMapError : public std::runtime_error {
public:
	loadMapError(std::string message);
};

class loadRawError : public std::runtime_error {
public:
	loadRawError(std::string message);
};

class mapFormatError : public std::runtime_error {
public:
	mapFormatError(std::string message);
};

class rawFormatError : public std::runtime_error {
public:
	rawFormatError(std::string message);
};


}

#endif /* EXCEPTIONS_H_ */
