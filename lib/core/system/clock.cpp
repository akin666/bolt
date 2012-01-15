/*
 * clock.cpp
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#include "clock.hpp"


namespace bolt
{

inline Time convertToTime( const timeval& time )
{
	return (time.tv_sec * 1000.0) + ( time.tv_usec * 0.001 );
}

Clock::Clock( Time current )
{
	gettimeofday( &tmpTime , NULL );
	start = convertToTime( tmpTime ) - current;
}

Clock::Clock( Seconds current , MicroSeconds us )
{
	gettimeofday( &tmpTime , NULL );

	start = tmpTime.tv_sec - current;
	ustart = tmpTime.tv_usec - us;

	// TODO! testing..
	while( ustart < 0 )
	{
		--start;
		ustart += 1000000;
	}
}

Clock::~Clock()
{
}

Time Clock::getCurrentTime()
{
	gettimeofday( &tmpTime , NULL );

	return convertToTime( tmpTime ) - start;
}

Time Clock::getUnixTime()
{
	gettimeofday( &tmpTime , NULL );

	return convertToTime( tmpTime );
}


void Clock::getCurrentTime( Seconds& s , MicroSeconds& us )
{
	gettimeofday( &tmpTime , NULL );

	s = tmpTime.tv_sec - start;
	us = tmpTime.tv_usec - ustart;
}

void Clock::getUnixTime( Seconds& s , MicroSeconds& us )
{
	gettimeofday( &tmpTime , NULL );

	s = tmpTime.tv_sec;
	us = tmpTime.tv_usec;
}
} // namespace bolt

