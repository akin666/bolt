/*
 * simpletenderercomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "simplerenderercontroller.hpp"
#include <component/common/positionproperty.hpp>
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

void SimpleRendererController::initialize() throw (std::exception)
{
	// already initialized?
	if( initialized )
	{
		return;
	}

	dependecies.insert( bolt::FenceController::RENDER );

	bolt::createSingleton<bolt::PositionProperty>()->initialize();
}

void SimpleRendererController::getDependencies(bolt::StringSet & dep)
{
	dep = dependecies;
}

void SimpleRendererController::attach(bolt::Entity & entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->attach( entity );
}

void SimpleRendererController::detach(bolt::Entity & entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->detach( entity );
}

void SimpleRendererController::start(bolt::ControllerNode& node)
{
	// do the rendering here.
}



