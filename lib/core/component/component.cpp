/*
 * Component.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "component.hpp"

namespace bolt
{

// SM_ID functionality
uint Component::sm_id = 0xFF;
uint Component::getNewId()
{
	return ++sm_id;
}

uint Component::getId() const
{
	return id;
}
// /SM_ID

Component::Component( std::string name , bool concurrent )
: id( getNewId() ),
  priority( 0xFF ),
  name( name ),
  concurrent( concurrent )
{
}

Component::~Component()
{
}

bool Component::isConcurrent() const
{
	return concurrent;
}

uint Component::getPriority() const
{
	return priority;
}

std::string Component::getName() const
{
	return name;
}

void Component::setPriority( uint prio )
{
	priority = prio;
}

bool Component::initialize()
{
	return true;
}

void Component::getDependencies( StringSet& dep )
{
}

} /* namespace bolt */
