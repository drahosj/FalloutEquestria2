/*
 * Logger.h
 *
 *  Created on: Aug 26, 2013
 *      Author: jake
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>

namespace foe {

class Logger {
public:
	Logger();
	virtual ~Logger();
	void log(std::string);
private:
	std::ofstream logfile;
	long openTime;
};

} /* namespace foe */
#endif /* LOGGER_H_ */
