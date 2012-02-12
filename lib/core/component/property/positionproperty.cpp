/*
 * positionproperty.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "positionproperty.hpp"

namespace bolt
{
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
	if( data.find( entity.getId() ) != data.end() )
	{
		return;
	}

	data[entity.getId()];
}

void PositionProperty::detach( bolt::Entity& entity )
{
	if( data.find( entity.getId() ) != data.end() )
	{
		data.erase( entity.getId() );
	}
}

Position& PositionProperty::get( bolt::uint entity )
{
	return data[entity];
}
}
