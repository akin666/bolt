/*
 * Component.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "component.hpp"
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
  concurrent( concurrent )
{
}

Component::~Component()
{
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

bool Component::before(Component & component)
{
	return false;
}

} /* namespace bolt */
