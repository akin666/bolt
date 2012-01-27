/*
 * ControllerNode.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "controllernode.hpp"
#include <threadpool>
#include "controllerwork.hpp"
#include <component/controller.hpp>

namespace bolt
{

ControllerNode::ControllerNode( Controller& controller , TQue<ControllerNode*>& finishQueu )
: controller( controller ),
  concurrent_reference_counting( 0 ),
  cycle( 0 ),
  finishQueu( finishQueu )
{
}

ControllerNode::ControllerNode( ControllerNode& other )
: controller( other.controller ),
  concurrent_reference_counting( other.concurrent_reference_counting ),
  cycle( other.cycle ),
  finishQueu( other.finishQueu )
{
}

ControllerNode::~ControllerNode()
{
}

NodeSet& ControllerNode::getDependencies()
{
	return dependencies;
}

NodeSet& ControllerNode::getChilds()
{
	return childs;
}

void ControllerNode::addReference()
{
	concurrent_reference_counting++;
}

void ControllerNode::releaseReference()
{
	concurrent_reference_counting--;

	// Signal the whatever, that this component finished.
	if( concurrent_reference_counting == 0 )
	{
		finishQueu.push( this );
	}
}

bool ControllerNode::isRunning()
{
	return concurrent_reference_counting > 0;
}

void ControllerNode::start( uint end )
{
	addReference();
	controller.start( *this );
	cycle = end;
	releaseReference();
}

void ControllerNode::schedule( ControllerWork& work )
{
	// Schedule the work in threadpools..
	addReference();

	if( bolt::getSingleton<bolt::ThreadPool>() != NULL )
	{
		bolt::getSingleton<bolt::ThreadPool>()->schedule( &work );
	}
	else if( work.begin() )
	{
		work.run();
		work.end();
	}
}

void ControllerNode::scheduleWork( Work& work )
{
	if( bolt::getSingleton<bolt::ThreadPool>() != NULL )
	{
		bolt::getSingleton<bolt::ThreadPool>()->schedule( &work );
	}
	else if( work.begin() )
	{
		work.run();
		work.end();
	}
}

Controller& ControllerNode::get()
{
	return controller;
}

uint ControllerNode::getCycle()
{
	return cycle;
}

void ControllerNode::setCycle( uint val )
{
	cycle = val;
}

void ControllerNode::finished( ControllerWork& work )
{
	releaseReference();
}

} /* namespace bolt */
