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


void Pipeline::removeFromRoot( ComponentNode *node )
{
	roots.erase( node );
}

void Pipeline::addToRoot( ComponentNode *node )
{
	if( node != NULL && node->getDependencies().size() == 0 )
	{
		// no parent.
		roots.insert( node );
	}
}

void Pipeline::resetCycle( uint val )
{
	for( std::map<std::string , ComponentNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
	{
		iter->second->setCycle( val );
	}
}

void Pipeline::attach( Component *component ) throw (std::exception)
{
	if( component == NULL )
	{
		return;
	}

	std::lock_guard<std::mutex> lock( mutex );

	// already has it
	if( nodeNameMap.find( component->getName() ) != nodeNameMap.end() )
	{
		return;
	}

	ComponentNode *node = new ComponentNode( *component , waitingQue );

	StringSet dependencies;
	component->getDependencies( dependencies );

	// Seek Parent dependencies.
	// If found, link em.
	std::map<std::string , ComponentNode*>::iterator citer;
	for( StringSet::iterator iter = dependencies.begin() ; iter != dependencies.end() ; ++iter )
	{
		citer = nodeNameMap.find( *iter );

		if( citer != nodeNameMap.end() )
		{
			// found!
			ComponentNode *dependencyNode = citer->second;

			node->getDependencies().insert( dependencyNode );
			dependencyNode->getChilds().insert( node );
		}
	}

	// Seek child dependencies.
	// If found, link em.
	std::string name = component->getName();
	for( std::map<std::string , ComponentNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
	{
		ComponentNode *dependencyNode = iter->second;

		// Reuse list..
		dependencyNode->getComponent().getDependencies( dependencies );

		// No dependency?
		if( dependencies.find( name ) == dependencies.end() )
		{
			continue;
		}

		// Dependency, link em.
		dependencyNode->getDependencies().insert( node );
		node->getChilds().insert( dependencyNode );

		if( dependencyNode->getDependencies().size() == 1 )
		{
			// First parent! Remove from root!
			removeFromRoot( dependencyNode );
		}
	}

	// try to add as root element..
	addToRoot( node );

	resetCycle( 0 );
}

void Pipeline::detach( Component *component ) throw (std::exception)
{
	if( component == NULL )
	{
		return;
	}

	std::lock_guard<std::mutex> lock( mutex );

	std::map<std::string , ComponentNode*>::iterator iter = nodeNameMap.find( component->getName() );

	// does not have it..
	if( iter == nodeNameMap.end() )
	{
		return;
	}

	ComponentNode *node = iter->second;

	// remove from namemap.
	nodeNameMap.erase( iter );

	if( node == NULL )
	{
		return;
	}

	// remove node from the lists.
	if( roots.find( node ) != roots.end() )
	{
		roots.erase( node );
	}

	// remove parent from childs
	// and link new child parent relation
	// or add to roots.
	bool root = node->getDependencies().size() > 0;
	for( NodeSet::iterator iter = node->getChilds().begin() ; iter != node->getChilds().end() ; ++iter )
	{
		(*iter)->getDependencies().erase( node );

		for( NodeSet::iterator piter = node->getDependencies().begin() ; piter != node->getDependencies().end() ; ++piter )
		{
			(*iter)->getDependencies().insert( *piter );
			(*piter)->getChilds().insert( *iter );
		}

		if( !root )
		{
			addToRoot( *iter );
		}
	}
}

void Pipeline::run() throw (std::exception)
{
	// Launch each component,
	std::lock_guard<std::mutex> lock( mutex );

	if( roots.size() < 1 )
	{
		return;
	}

	++cycle;

	ComponentNode *current;
	ComponentNode *child;
	ComponentNode *parent;
	bool qualified;

	// Sort concurrent and nonconcurrent components.
	concurrent.clear();
	nonConcurrent.clear();
	for( NodeSet::iterator iter = roots.begin() ; iter != roots.end() ; ++iter )
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
			if( current->getCycle() >= cycle || current->isRunning() )
			{
				continue;
			}

			current->start( cycle );
			++running;
		}
		// run all single threaded, non-concurrent components.
		for( NodeSet::iterator iter = nonConcurrent.begin() ; iter != nonConcurrent.end() ; ++iter )
		{
			current = *iter;

			// already running or finished, do not run again.
			if( current->getCycle() >= cycle || current->isRunning() )
			{
				continue;
			}

			current->start( cycle );
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

					if( parent->getCycle() != cycle || parent->isRunning() )
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
