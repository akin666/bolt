/*
 * namecomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "namecomponent.hpp"
#include "nameproperty.hpp"
#include <singleton>

const std::string NameComponent::KEY("name");

NameComponent::NameComponent()
: bolt::Component( KEY )
{
}

NameComponent::~NameComponent()
{
}

bool NameComponent::initialize()
{
	return bolt::Singleton<NameProperty>::create()->initialize();
}

void NameComponent::getDependencies(bolt::StringSet & dep)
{
}

void NameComponent::attach(bolt::Entity & entity)
{
	bolt::Singleton<NameProperty>::get()->attach( entity );
}

void NameComponent::detach(bolt::Entity & entity)
{
	bolt::Singleton<NameProperty>::get()->detach( entity );
}

void NameComponent::start(bolt::ComponentNode & node)
{
}

