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
: concurrent_reference_counting( 0 )
{
}

ComponentNode::ComponentNode( ComponentNode& other )
{
}

ComponentNode::~ComponentNode()
{
}

void ComponentNode::addReference()
{
	concurrent_reference_counting++;
}

void ComponentNode::releaseReference()
{
	if( concurrent_reference_counting-- <= 0 )
	{
		// component finished!!
	}
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

void ComponentNode::finished( ComponentWork& work )
{
	releaseReference();
}

} /* namespace bolt */
