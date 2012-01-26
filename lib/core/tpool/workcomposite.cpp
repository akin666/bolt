/*
 * workcomposite.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "workcomposite.hpp"

namespace bolt
{

WorkComposite::WorkComposite()
: running( false )
{
}

WorkComposite::~WorkComposite()
{
}

void WorkComposite::setRunning( bool state )
{
	std::lock_guard<std::mutex> lock(mutex);
	running = state;
}

bool WorkComposite::getRunning()
{
	std::lock_guard<std::mutex> lock(mutex);
	return running;
}

bool WorkComposite::begin()
{
	return true;
}

void WorkComposite::run()
{
	setRunning( true );
	Work *current;

	while( ( current = work.pop() ) != NULL )
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

void WorkComposite::end()
{
}

bool WorkComposite::isRunning()
{
	return getRunning();
}

void WorkComposite::push( Work *work )
{
	this->work.push( work );
}

} /* namespace bolt */

