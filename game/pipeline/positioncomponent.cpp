/*
 * positioncomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "positioncomponent.hpp"
#include "positionproperty.hpp"
#include <singleton>

const std::string PositionComponent::KEY("position");

PositionComponent::PositionComponent()
: bolt::Component( KEY )
{
}

PositionComponent::~PositionComponent()
{
}

bool PositionComponent::initialize()
{
	return bolt::Singleton<PositionProperty>::create()->initialize();
}

void PositionComponent::getDependencies(bolt::StringSet & dep)
{
}

void PositionComponent::attach(bolt::Entity & entity)
{
	bolt::Singleton<PositionProperty>::get()->attach( entity );
}

void PositionComponent::detach(bolt::Entity & entity)
{
	bolt::Singleton<PositionProperty>::get()->detach( entity );
}

void PositionComponent::start(bolt::ComponentNode & node)
{
}


