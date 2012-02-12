/*
 * ControllerWork.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "controllerwork.hpp"
#include "controllernode.hpp"
#include <iostream>

namespace bolt
{

ControllerWork::ControllerWork()
: parent( NULL )
{
}

ControllerWork::~ControllerWork()
{
}

void ControllerWork::set( ControllerNode *co )
{
	parent = co;
}

bool ControllerWork::begin()
{
	return true;
}

void ControllerWork::end()
{
	if( parent != NULL )
	{
		parent->finished( *this );
	}
}

} /* namespace bolt */
