/*
 * componentwork.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "componentwork.hpp"
#include "component.hpp"
#include <iostream>

namespace bolt
{

ComponentWork::ComponentWork()
: parent( NULL )
{
}

ComponentWork::~ComponentWork()
{
}

void ComponentWork::setComponent( Component *component )
{
	parent = component;
}

bool ComponentWork::begin()
{
	return true;
}

void ComponentWork::end()
{
	if( parent != NULL )
	{
		parent->finished( *this );
	}
}

} /* namespace bolt */
