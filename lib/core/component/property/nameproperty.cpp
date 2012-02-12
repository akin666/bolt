/*
 * nameproperty.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "nameproperty.hpp"

namespace bolt
{
const std::string NameProperty::KEY("name");

NameProperty::NameProperty()
: bolt::Property( KEY )
{
}

NameProperty::~NameProperty()
{
}

void NameProperty::initialize() throw (std::exception)
{
}

void NameProperty::attach( bolt::Entity& entity )
{
	// already attached?
	if( data.find( entity.getId() ) != data.end() )
	{
		return;
	}

	data[entity.getId()] = "";
}

void NameProperty::detach( bolt::Entity& entity )
{
	if( data.find( entity.getId() ) != data.end() )
	{
		data.erase( entity.getId() );
	}
}

std::string& NameProperty::get( bolt::Entity& entity )
{
	return data[entity.getId()];
}
}
