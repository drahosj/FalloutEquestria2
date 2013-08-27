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
	openTime = std::time(0);
	sprintf(buffer, "%d", openTime);
	std::string filename = "log/";
	filename.append(buffer);
	filename.append(".log");
	logfile.open(filename.c_str());
}

void Logger::log(std::string s) {
	std::string logstring = "[T+";
	char buffer[16];
	sprintf(buffer, "%08d", std::time(0) - openTime);
	logstring += buffer;
	logstring += "] ";
	logstring += s;
	logstring += "\n";
	logfile << logstring;
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
	logfile.close();
}

} /* namespace foe */
