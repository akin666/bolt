/*
 * prototype.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "prototype.hpp"
#include <iostream>
#include "entity.hpp"

namespace bolt
{

Prototype::Prototype()
{
}

Prototype::~Prototype()
{
}

void Prototype::add( Controller& controller )
{
	// already in list?
	if( controllers.find( &controller) != controllers.end() )
	{
		controllers.insert( &controller );
	}
}

void Prototype::attach( Entity& entity )
{
	for( ControllerSet::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		(*iter)->attach( entity );
	}
}

Entity Prototype::create()
{
	Entity entity;

	attach( entity );

	return entity;
}

} /* namespace bolt */

