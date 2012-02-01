/*
 * entity.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "entity.hpp"

namespace bolt
{

uint Entity::mId = 1;

uint Entity::createId()
{
	return mId++;
}

Entity::Entity()
: id( createId() )
{
}

Entity::Entity( const Entity& other )
: id( other.id )
{
}

uint Entity::getId()
{
	return id;
}

Entity::operator uint()
{
	return id;
}

Entity& Entity::operator =( const Entity& other )
{
	id = other.id;
	return *this;
}

}

