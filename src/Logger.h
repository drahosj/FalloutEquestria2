/*
 * Logger.h
 *
 *  Created on: Aug 26, 2013
 *      Author: jake
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>

namespace foe {

class Logger {
public:
	Logger();
	virtual ~Logger();
private:
	std::ofstream logfile;
};

} /* namespace foe */
#endif /* LOGGER_H_ */
