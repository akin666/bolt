/*
 * CompositeWork.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "compositework.hpp"

namespace bolt
{

CompositeWork::CompositeWork()
: running( false )
{
}

CompositeWork::~CompositeWork()
{
}

void CompositeWork::setRunning( bool state )
{
	std::lock_guard<std::mutex> lock(mutex);
	running = state;
}

bool CompositeWork::getRunning()
{
	std::lock_guard<std::mutex> lock(mutex);
	return running;
}

bool CompositeWork::begin()
{
	return true;
}

void CompositeWork::run()
{
	setRunning( true );
	Work *current;

	while( ( current = work.pop( work.RETURN_NULL_IF_EMPTY ) ) != NULL )
	{
		if( current->begin() )
		{
			current->run();
			current->end();
		}
		else
		{
			work.push( current );
		}
	}
	setRunning( false );
}

void CompositeWork::end()
{
}

bool CompositeWork::isRunning()
{
	return getRunning();
}

void CompositeWork::push( Work *work )
{
	this->work.push( work );
}

} /* namespace bolt */

