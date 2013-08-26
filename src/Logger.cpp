/*
 * Logger.cpp
 *
 *  Created on: Aug 26, 2013
 *      Author: jake
 */

#include "Logger.h"
#include <ctime>
#include <stdlib.h>
#include <string>

namespace foe {

Logger::Logger() {
	// TODO Auto-generated constructor stub
	char buffer[32]; //more than enough for a Unix timestamp
	sprintf(buffer, "%d", std::time(0));
	std::string filename = "log/";
	filename.append(buffer);
	filename.append(".log");
	logfile.open(filename.c_str());
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

} /* namespace foe */
