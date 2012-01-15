/*
 * Component.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "component.hpp"
#include <threadpool>
#include "componentwork.hpp"

namespace bolt
{

// SM_ID functionality
unsigned int Component::sm_id = 0xFF;
unsigned int Component::getNewId()
{
	return ++sm_id;
}

unsigned int Component::getId() const
{
	return id;
}
// /SM_ID

Component::Component( bool concurrent )
: id( getNewId() ),
  concurrent( concurrent ),
  concurrent_reference_counting( 0 )
{
}

Component::~Component()
{
}

void Component::addReference()
{
	concurrent_reference_counting++;
}

void Component::releaseReference()
{
	if( concurrent_reference_counting-- <= 0 )
	{
		// component finished!!
	}
}

bool Component::isConcurrent()
{
	return concurrent;
}

unsigned int Component::getPriority()
{
	return priority;
}

void Component::setPriority( unsigned int prio )
{
	priority = prio;
}

void Component::schedule( ComponentWork& work )
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

void Component::finished( ComponentWork& work )
{
	releaseReference();
}

bool Component::before(Component & component)
{
	return false;
}

} /* namespace bolt */
