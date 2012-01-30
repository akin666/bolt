/*
 * pipeline.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "pipeline.hpp"
#include "controller.hpp"
#include "tools/controllernode.hpp"

namespace bolt
{

Pipeline::Pipeline()
{
	clear();
}

Pipeline::~Pipeline()
{
	clear();
}

void Pipeline::clear()
{
	std::lock_guard<std::mutex> lock( mutex );
	std::lock_guard<std::mutex> addlock( addSetMutex );
	std::lock_guard<std::mutex> removelock( removeSetMutex );

	for( std::map<std::string , ControllerNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
	{
		delete iter->second;
	}

	nodeNameMap.clear();
	roots.clear();
	nonConcurrent.clear();
	concurrent.clear();
	addSet.clear();
	removeSet.clear();

	cycle = CYCLE_NULL + 1;
}

void Pipeline::setCycle( uint val )
{
	std::lock_guard<std::mutex> lock( mutex );

	cycle = val;

	for( std::map<std::string , ControllerNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
	{
		iter->second->setCycle( cycle );
	}
}

uint Pipeline::getCycle()
{
	return cycle;
}

void Pipeline::addToRoot( ControllerNode *node )
{
	if( node != NULL && node->getDependencies().size() == 0 )
	{
		// no parent.
		roots.insert( node );
	}
}

void Pipeline::attach( Controller *controller ) throw (std::exception)
{
	if( controller == NULL )
	{
		return;
	}

	std::lock_guard<std::mutex> lock( addSetMutex );
	addSet.insert( controller );
}

void Pipeline::detach( Controller *controller ) throw (std::exception)
{
	if( controller == NULL )
	{
		return;
	}

	std::lock_guard<std::mutex> lock( removeSetMutex );
	removeSet.insert( controller );
}

void Pipeline::run() throw (std::exception)
{
	std::lock_guard<std::mutex> lock( mutex );
	if( roots.size() < 1 )
	{
		runRemoveSet();
		runAddSet();

		return;
	}

	++cycle;

	// Launch each controller,
	ControllerNode *current;
	ControllerNode *child;
	ControllerNode *parent;
	bool qualified;

	// Sort concurrent and nonconcurrent controllers.
	concurrent.clear();
	nonConcurrent.clear();
	for( NodeSet::iterator iter = roots.begin() ; iter != roots.end() ; ++iter )
	{
		current = *iter;

		if( current->get().isConcurrent() )
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
		// run all concurrent controllers first.
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
		// run all single threaded, non-concurrent controllers.
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
				if( child->get().isConcurrent() )
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

	runRemoveSet();
	runAddSet();
}

void Pipeline::runAddSet()
{
	std::lock_guard<std::mutex> lock( addSetMutex );

	for( ControllerSet::iterator addSetIter = addSet.begin() ; addSetIter != addSet.end() ; ++addSetIter )
	{
		Controller *controller = *addSetIter;

		// already has it
		if( nodeNameMap.find( controller->getName() ) != nodeNameMap.end() )
		{
			continue;
		}

		ControllerNode *node = new ControllerNode( *controller , waitingQue );

		StringSet dependencies;
		controller->getDependencies( dependencies );

		// Seek Parent dependencies.
		// If found, link em.
		std::map<std::string , ControllerNode*>::iterator citer;
		for( StringSet::iterator stringSetIter = dependencies.begin() ; stringSetIter != dependencies.end() ; ++stringSetIter )
		{
			citer = nodeNameMap.find( *stringSetIter );

			if( citer != nodeNameMap.end() )
			{
				// found!
				ControllerNode *dependencyNode = citer->second;

				node->getDependencies().insert( dependencyNode );
				dependencyNode->getChilds().insert( node );
			}
		}

		// Seek child dependencies.
		// If found, link em.
		std::string name = controller->getName();
		for( std::map<std::string , ControllerNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
		{
			ControllerNode *dependencyNode = iter->second;

			// Reuse list..
			dependencyNode->get().getDependencies( dependencies );

			// No dependency?
			if( dependencies.find( name ) == dependencies.end() )
			{
				continue;
			}

			// Dependency, link em.
			dependencyNode->getDependencies().insert( node );
			node->getChilds().insert( dependencyNode );

			if( dependencyNode->getDependencies().size() <= 1 )
			{
				// First parent! Remove from root!
				roots.erase( node );
			}
		}

		// try to add as root element..
		addToRoot( node );

		node->setCycle( cycle );
	}
	addSet.clear();
}

void Pipeline::runRemoveSet()
{
	std::lock_guard<std::mutex> lock( removeSetMutex );

	ControllerNode *node;
	for( ControllerSet::iterator iter = removeSet.begin() ; iter != removeSet.end() ; ++iter )
	{
		Controller *controller = *iter;

		{
			std::map<std::string , ControllerNode*>::iterator nodeNameMapIter = nodeNameMap.find( controller->getName() );

			// does not have it..
			if( nodeNameMapIter == nodeNameMap.end() )
			{
				return;
			}

			ControllerNode *node = nodeNameMapIter->second;

			// remove from namemap.
			nodeNameMap.erase( nodeNameMapIter );

			if( node == NULL )
			{
				continue;
			}
		}

		// Remove node from roots
		if( roots.find( node ) != roots.end() )
		{
			roots.erase( node );
		}

		// Remove node from childs
		for( NodeSet::iterator targetIter = node->getChilds().begin() ; targetIter != node->getChilds().end() ; ++targetIter )
		{
			(*targetIter)->getDependencies().erase( node );

			// check if the child becomes a root node.
			if( (*targetIter)->getDependencies().size() == 0 )
			{
				roots.insert( (*targetIter) );
			}
		}

		// Remove node from dependencies.
		for( NodeSet::iterator targetIter = node->getDependencies().begin() ; targetIter != node->getDependencies().end() ; ++targetIter )
		{
			(*targetIter)->getChilds().erase( node );
		}

		// destroy the node.
		delete node;
	}
	removeSet.clear();
}

} /* namespace bolt */
