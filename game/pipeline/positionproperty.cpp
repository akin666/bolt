/*
 * positionproperty.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "positionproperty.hpp"

const std::string PositionProperty::KEY("position");

PositionProperty::PositionProperty()
: bolt::Property( KEY )
{
}

PositionProperty::~PositionProperty()
{
}

void PositionProperty::initialize() throw (std::exception)
{
}

void PositionProperty::attach( bolt::Entity& entity )
{
	// already attached?
	if( data.find( entity ) != data.end() )
	{
		return;
	}

	data[entity];
}

void PositionProperty::detach( bolt::Entity& entity )
{
	// This property is not really detachable. once it has been attached, it cannot be detached.
	if( data.find( entity ) != data.end() )
	{
	//	data.erase( entity );
	}
}

PositionProperty::Data& PositionProperty::get( bolt::Entity& entity )
{
	return data[entity];
}
