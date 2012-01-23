/*
 * simpletenderercomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "simplerenderercontroller.hpp"
#include "positionproperty.hpp"
#include <singleton>
#include <component/common/fencecontroller.hpp>

const std::string SimpleRendererController::KEY("simplerenderer");

SimpleRendererController::SimpleRendererController()
: bolt::Controller( KEY , false ),
  initialized( false )
{
}

SimpleRendererController::~SimpleRendererController()
{
}

bool SimpleRendererController::initialize()
{
	// already initialized?
	if( initialized )
	{
		return true;
	}

	dependecies.insert( bolt::FenceController::RENDER );

	return bolt::Singleton<PositionProperty>::create()->initialize();
}

void SimpleRendererController::getDependencies(bolt::StringSet & dep)
{
	dep = dependecies;
}

void SimpleRendererController::attach(bolt::Entity & entity)
{
	bolt::Singleton<PositionProperty>::get()->attach( entity );
}

void SimpleRendererController::detach(bolt::Entity & entity)
{
	bolt::Singleton<PositionProperty>::get()->detach( entity );
}

void SimpleRendererController::start(bolt::ControllerNode& node)
{
	// do the rendering here.
}



