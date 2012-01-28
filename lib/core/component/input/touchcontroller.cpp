/*
 * touchcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "touchcontroller.hpp"

namespace bolt
{
const std::string TouchController::KEY("touch");

TouchController::TouchController()
: bolt::Controller( KEY )
{
}

TouchController::~TouchController()
{
}

void TouchController::initialize() throw (std::exception)
{
}

void TouchController::getDependencies(bolt::StringSet & dep)
{
}

void TouchController::attach(bolt::Entity & entity)
{
}

void TouchController::detach(bolt::Entity & entity)
{
}

void TouchController::start(bolt::ControllerNode & node)
{
}

void TouchController::startTouch(int id, float x, float y)
{
}

void TouchController::continueTouch(int id, float x, float y)
{
}

void TouchController::endTouch(int id, float x, float y)
{
}
}
