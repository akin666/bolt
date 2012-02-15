/*
 * cameraproperty.cpp
 *
 *  Created on: 13.2.2012
 *      Author: akin
 */

#include "cameraproperty.hpp"
#include "positionproperty.hpp"
#include <singleton>

namespace bolt
{
const std::string CameraProperty::KEY("camera");

CameraProperty::CameraProperty()
: bolt::Property( KEY ),
  current( Entity::null )
{
}

CameraProperty::~CameraProperty()
{
}

void CameraProperty::initialize()
{
}

void CameraProperty::attach( bolt::Entity& entity )
{
	// already attached?
	if( data.find( entity.getId() ) != data.end() )
	{
		return;
	}

	data[entity.getId()];
}

void CameraProperty::detach( bolt::Entity& entity )
{
	if( data.find( entity.getId() ) != data.end() )
	{
		data.erase( entity.getId() );
	}
}

glm::mat4 CameraProperty::lenseMatrix( bolt::uint entity )
{
	return data[entity].lense;
}

glm::mat4 CameraProperty::positionMatrix( bolt::uint entity )
{
	return glm::inverse( getSingleton<PositionProperty>()->toMatrix( entity ) );
}

Camera& CameraProperty::get( bolt::uint entity )
{
	return data[entity];
}

Entity CameraProperty::getCurrent()
{
	return current;
}

void CameraProperty::setCurrent( Entity& entity )
{
	this->current = entity;
}

} /* namespace bolt */

