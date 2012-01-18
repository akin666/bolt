/*
 * componentnode.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "componentnode.hpp"
#include <threadpool>
#include "componentwork.hpp"

namespace bolt
{

ComponentNode::ComponentNode( Component& component )
: concurrent_reference_counting( 0 ),
  time( 0 )
{
}

ComponentNode::ComponentNode( ComponentNode& other )
{
}

ComponentNode::~ComponentNode()
{
}

std::deque<ComponentNode *>& ComponentNode::getDependencies()
{
	return dependencies;
}

std::deque<ComponentNode *>& ComponentNode::getChilds()
{
	return childs;
}

void ComponentNode::addReference()
{
	concurrent_reference_counting++;
}

void ComponentNode::releaseReference()
{
	concurrent_reference_counting--;
}

bool ComponentNode::isRunning()
{
	return concurrent_reference_counting <= 0;
}

void ComponentNode::start( unsigned int start , unsigned int end )
{
	addReference();
	time = start;
	component.start( *this );
	time = end;
	releaseReference();
}

void ComponentNode::schedule( ComponentWork& work )
{
	// Schedule the work in threadpools..
	addReference();

	if( bolt::Singleton<bolt::ThreadPool>::get() != NULL )
	{
		bolt::Singleton<bolt::ThreadPool>::get()->schedule( &work );
	}
	else if( work.begin() )
	{
		work.run();
		work.end();
	}
}

Component& ComponentNode::getComponent()
{
	return component;
}

unsigned int ComponentNode::getTime()
{
	return time;
}

void ComponentNode::finished( ComponentWork& work )
{
	releaseReference();
}

} /* namespace bolt */
