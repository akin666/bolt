/*
 * pipeline.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "pipeline.hpp"

namespace bolt
{

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::attach( Component *component ) throw (std::exception)
{
	std::lock_guard<std::mutex> lock( mutex );

	net.add( component );
}

void Pipeline::run() throw (std::exception)
{
	// Launch each component,
	std::lock_guard<std::mutex> lock( mutex );

	net.getRoot( temp );

	if( temp.size() < 1 )
	{
		return;
	}

	unsigned int previousTime = temp.front()->time;
	unsigned int currentTime = previousTime + 1;

	ComponentNode *current;
	ComponentNode *child;
	ComponentNode *parent;
	bool qualified;

	// Sort concurrent and nonconcurrent components.
	concurrent.clear();
	nonConcurrent.clear();
	for( int i = temp.size() - 1 ; i >= 0 ; --i )
	{
		current = temp.at(i);

		if( current->getComponent().isConcurrent() )
		{
			concurrent.push_back( current );
		}
		else
		{
			nonConcurrent.push_back( current );
		}
	}

	unsigned int running = 0;
	do
	{
		// foreach
		// run all concurrent components first.
		for( int i = concurrent.size() - 1 ; i >= 0 ; --i )
		{
			current = concurrent.at(i);

			// already running or finished, do not run again.
			if( current->time >= currentTime || current->isRunning() )
			{
				continue;
			}

			current->componentStart( waitingQue , previousTime , currentTime );
			++running;
		}
		// run all single threaded, non-concurrent components.
		for( int i = nonConcurrent.size() - 1 ; i >= 0 ; --i )
		{
			current = nonConcurrent.at(i);

			// already running or finished, do not run again.
			if( current->time >= currentTime || current->isRunning() )
			{
				continue;
			}

			current->componentStart( waitingQue , previousTime , currentTime );
			++running;
		}

		// Clear the queu
		concurrent.clear();
		nonConcurrent.clear();

		current = waitingQue.pop();
		--running;

		if( current != NULL )
		{
			// Get child list..
			for( int i = current->childs.size() - 1 ; i >= 0 ; --i )
			{
				// Check if child is qualified.
				child = current->childs.at( i );

				// Are all parents in currentTime & running is off?
				qualified = true;
				for( int j = child->dependencies.size() - 1 ; j >= 0 ; --j )
				{
					parent = child->dependencies.at( j );

					if( parent->time != currentTime || parent->isRunning() )
					{
						qualified = false;
						break;
					}
				}
				if( !qualified )
				{
					// parent flunked!
					continue;
				}

				// Sort childs to correct places.
				if( child->getComponent().isConcurrent() )
				{
					concurrent.push_back( child );
				}
				else
				{
					nonConcurrent.push_back( child );
				}
			}
		}
	}
	while( running > 0 || concurrent.size() > 0 || nonConcurrent.size() > 0 );
}

} /* namespace bolt */
