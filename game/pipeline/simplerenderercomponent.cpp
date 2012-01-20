/*
 * simpletenderercomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "simplerenderercomponent.hpp"
#include "positionproperty.hpp"
#include <singleton>
#include <component/common/fencecomponent.hpp>

const std::string SimpleRendererComponent::KEY("simplerenderer");

SimpleRendererComponent::SimpleRendererComponent()
: bolt::Component( KEY ),
  initialized( false )
{
}

SimpleRendererComponent::~SimpleRendererComponent()
{
}

bool SimpleRendererComponent::initialize()
{
	// already initialized?
	if( initialized )
	{
		return true;
	}

	dependecies.insert( bolt::FenceComponent::RENDER );

	return bolt::Singleton<PositionProperty>::create()->initialize();
}

void SimpleRendererComponent::getDependencies(bolt::StringSet & dep)
{
	dep = dependecies;
}

void SimpleRendererComponent::attach(bolt::Entity & entity)
{
	bolt::Singleton<PositionProperty>::get()->attach( entity );
}

void SimpleRendererComponent::detach(bolt::Entity & entity)
{
	bolt::Singleton<PositionProperty>::get()->detach( entity );
}

void SimpleRendererComponent::start(bolt::ComponentNode & node)
{
}



