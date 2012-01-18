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

Component::Component( std::string name , bool concurrent )
: id( getNewId() ),
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

unsigned int Component::getPriority() const
{
	return priority;
}

std::string Component::getName() const
{
	return name;
}

void Component::setPriority( unsigned int prio )
{
	priority = prio;
}

void Component::getDependencies( StringSet& dep )
{
}

} /* namespace bolt */
