/*
 * fencecomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "fencecontroller.hpp"

namespace bolt
{

const std::string FenceController::INPUT("input");
const std::string FenceController::SIMULATION("simulation");
const std::string FenceController::LOGIC("logic");
const std::string FenceController::RENDER("render");
const std::string FenceController::POSTPROCESS("postprocess");

FenceController::FenceController( std::string fencename , bolt::StringSet& dependencies )
: bolt::Controller( fencename ),
  dependencies( dependencies )
{
}

FenceController::~FenceController()
{
}

void FenceController::initialize() throw (std::exception)
{
}

void FenceController::getDependencies( bolt::StringSet& dep )
{
	dep = dependencies;
}

void FenceController::attach( bolt::Entity& entity )
{
}

void FenceController::detach( bolt::Entity& entity )
{
}

void FenceController::start( bolt::ControllerNode& node )
{
}
}
