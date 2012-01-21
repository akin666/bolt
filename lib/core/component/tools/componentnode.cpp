/*
 * componentnode.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "componentnode.hpp"
#include <threadpool>
#include "componentwork.hpp"
#include <component/component.hpp>

namespace bolt
{

ComponentNode::ComponentNode( Component& component , TQue<ComponentNode*>& finishQueu )
: component( component ),
  concurrent_reference_counting( 0 ),
  cycle( 0 ),
  finishQueu( finishQueu )
{
}

ComponentNode::ComponentNode( ComponentNode& other )
: component( other.component ),
  concurrent_reference_counting( other.concurrent_reference_counting ),
  cycle( other.cycle ),
  finishQueu( other.finishQueu )
{
}

ComponentNode::~ComponentNode()
{
}

NodeSet& ComponentNode::getDependencies()
{
	return dependencies;
}

NodeSet& ComponentNode::getChilds()
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

	// Signal the whatever, that this component finished.
	if( concurrent_reference_counting == 0 )
	{
		finishQueu.push( this );
	}
}

bool ComponentNode::isRunning()
{
	return concurrent_reference_counting > 0;
}

void ComponentNode::start( uint end )
{
	addReference();
	component.start( *this );
	cycle = end;
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

void ComponentNode::scheduleWork( Work& work )
{
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

uint ComponentNode::getCycle()
{
	return cycle;
}

void ComponentNode::setCycle( uint val )
{
	cycle = val;
}

void ComponentNode::finished( ComponentWork& work )
{
	releaseReference();
}

} /* namespace bolt */
