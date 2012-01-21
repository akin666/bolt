/*
 * property.cpp
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#include "property.hpp"

namespace bolt
{

uint Property::sm_id = 0xFF;

uint Property::getNewId()
{
	return sm_id++;
}

Property::Property( std::string name )
: id( getNewId() ),
  name( name )
{
}

Property::~Property()
{
}

bool Property::initialize()
{
	return true;
}

std::string Property::getName() const
{
	return name;
}

unsigned int Property::getId() const
{
	return id;
}

} /* namespace bolt */
