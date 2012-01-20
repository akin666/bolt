/*
 * fencecomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "fencecomponent.hpp"

namespace bolt
{

const std::string FenceComponent::INPUT("input");
const std::string FenceComponent::SIMULATION("simulation");
const std::string FenceComponent::LOGIC("logic");
const std::string FenceComponent::RENDER("render");
const std::string FenceComponent::POSTPROCESS("postprocess");

FenceComponent::FenceComponent( std::string fencename , bolt::StringSet& dependencies )
: bolt::Component( fencename ),
  dependencies( dependencies )
{
}

FenceComponent::~FenceComponent()
{
}

bool FenceComponent::initialize()
{
	return true;
}

void FenceComponent::getDependencies( bolt::StringSet& dep )
{
	dep = dependencies;
}

void FenceComponent::attach( bolt::Entity& entity )
{
}

void FenceComponent::detach( bolt::Entity& entity )
{
}

void FenceComponent::start( bolt::ComponentNode& node )
{
}
}
