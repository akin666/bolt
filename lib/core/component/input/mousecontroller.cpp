/*
 * mousecomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "mousecontroller.hpp"

namespace bolt
{
const std::string MouseController::KEY("mouse");

MouseController::MouseController()
: bolt::Controller( KEY )
{
}

MouseController::~MouseController()
{
}

void MouseController::initialize() throw (std::exception)
{
}

void MouseController::getDependencies(bolt::StringSet & dep)
{
}

void MouseController::attach(bolt::Entity & entity)
{
}

void MouseController::detach(bolt::Entity & entity)
{
}

void MouseController::start(bolt::ControllerNode & node)
{
}

void MouseController::handleMouseMove(float x, float y)
{
}

void MouseController::handleMouseButton(bolt::Button button, float state)
{
}

void MouseController::handleMouseWheel(float val)
{
}
}

