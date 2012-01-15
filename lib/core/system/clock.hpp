/*
 * clock
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef BOLT_CLOCK_H_
#define BOLT_CLOCK_H_

#include <sys/time.h>
#include <common>

namespace bolt
{

class Clock
{
protected:
	unsigned int start;
	unsigned int ustart;
	timeval tmpTime;
public:
	Clock( Time current = 0 );
	Clock( Seconds current , MicroSeconds us );
	virtual ~Clock();

	Time getCurrentTime();
	Time getUnixTime();

	void getCurrentTime( Seconds& s , MicroSeconds& us );
	void getUnixTime( Seconds& s , MicroSeconds& us );
};
} // namespace bolt

#endif

