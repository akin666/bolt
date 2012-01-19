/*
 * prototype.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "prototype.hpp"
#include <iostream>

namespace bolt
{

Prototype::Prototype()
{
}

Prototype::~Prototype()
{
}

void Prototype::add( Component& component )
{
	// already in list?
	if( components.find( &component) != components.end() )
	{
		components.insert( &component );
	}
}

void Prototype::attach( Entity& entity )
{
	for( ComponentSet::iterator iter = components.begin() ; iter != components.end() ; ++iter )
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

