/*
 * log.hpp
 *
 *  Created on: 8.1.2012
 *      Author: akin
 */

#ifndef LOG_HPP_
#define LOG_HPP_

#include <ostream>

namespace bolt
{
class Log
{
public:
	// Logging MUST be initialized at CTOR!
	Log();
	virtual ~Log();

	virtual std::ostream& error();
	virtual std::ostream& warning();
	virtual std::ostream& log();
	virtual std::ostream& out();
};
}

#endif /* Log */
