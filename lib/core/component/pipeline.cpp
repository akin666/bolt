/*
 * pipeline.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "pipeline.hpp"
#include "component.hpp"
#include "tools/componentnode.hpp"

namespace bolt
{

Pipeline::Pipeline()
: cycle( 0 )
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::setCycle( uint val )
{
	cycle = val;
}

uint Pipeline::getCycle()
{
	return cycle;
}

void Pipeline::attach( Component *component ) throw (std::exception)
{
	std::lock_guard<std::mutex> lock( mutex );

	tree.add( component );
}

void Pipeline::detach( Component *component ) throw (std::exception)
{
	std::lock_guard<std::mutex> lock( mutex );

	tree.remove( component );
}

void Pipeline::run() throw (std::exception)
{
	// Launch each component,
	std::lock_guard<std::mutex> lock( mutex );

	tree.getRoots( temp );

	if( temp.size() < 1 )
	{
		return;
	}

	uint currentCycle = cycle + 1;

	ComponentNode *current;
	ComponentNode *child;
	ComponentNode *parent;
	bool qualified;

	// Sort concurrent and nonconcurrent components.
	concurrent.clear();
	nonConcurrent.clear();
	for( NodeSet::iterator iter = temp.begin() ; iter != temp.end() ; ++iter )
	{
		current = *iter;

		if( current->getComponent().isConcurrent() )
		{
			concurrent.insert( current );
		}
		else
		{
			nonConcurrent.insert( current );
		}
	}

	unsigned int running = 0;
	do
	{
		// foreach
		// run all concurrent components first.
		for( NodeSet::iterator iter = concurrent.begin() ; iter != concurrent.end() ; ++iter )
		{
			current = *iter;

			// already running or finished, do not run again.
			if( current->getCycle() >= currentCycle || current->isRunning() )
			{
				continue;
			}

			current->start( currentCycle );
			++running;
		}
		// run all single threaded, non-concurrent components.
		for( NodeSet::iterator iter = nonConcurrent.begin() ; iter != nonConcurrent.end() ; ++iter )
		{
			current = *iter;

			// already running or finished, do not run again.
			if( current->getCycle() >= currentCycle || current->isRunning() )
			{
				continue;
			}

			current->start( currentCycle );
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
			for( NodeSet::iterator iter = current->getChilds().begin() ; iter != current->getChilds().end() ; ++iter )
			{
				// Check if child is qualified.
				child = *iter;

				// Are all parents in currentTime & running is off?
				qualified = true;
				for( NodeSet::iterator parentIter = child->getDependencies().begin() ; parentIter != child->getDependencies().end() ; ++parentIter )
				{
					parent = *parentIter;

					if( parent->getCycle() != currentCycle || parent->isRunning() )
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
					concurrent.insert( child );
				}
				else
				{
					nonConcurrent.insert( child );
				}
			}
		}
	}
	while( running > 0 || concurrent.size() > 0 || nonConcurrent.size() > 0 );
}

} /* namespace bolt */
