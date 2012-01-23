/*
 * controller.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "controller.hpp"

namespace bolt
{

// SM_ID functionality
uint Controller::sm_id = 0xFF;
uint Controller::getNewId()
{
	return ++sm_id;
}

uint Controller::getId() const
{
	return id;
}
// /SM_ID

Controller::Controller( std::string name , bool concurrent )
: id( getNewId() ),
  priority( 0xFF ),
  name( name ),
  concurrent( concurrent )
{
}

Controller::~Controller()
{
}

bool Controller::isConcurrent() const
{
	return concurrent;
}

uint Controller::getPriority() const
{
	return priority;
}

std::string Controller::getName() const
{
	return name;
}

void Controller::setPriority( uint prio )
{
	priority = prio;
}

bool Controller::initialize()
{
	return true;
}

void Controller::getDependencies( StringSet& dep )
{
}

} /* namespace bolt */
