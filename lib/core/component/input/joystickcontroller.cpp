/*
 * joystickcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "joystickcontroller.hpp"
#include <component/entity.hpp>

namespace bolt
{
const std::string JoystickController::KEY("joystick");

JoystickController::JoystickController()
: bolt::Controller( KEY )
{
}

JoystickController::~JoystickController()
{
}

void JoystickController::initialize() throw (std::exception)
{
}

void JoystickController::getDependencies(bolt::StringSet & dep)
{
}

void JoystickController::attach(bolt::Entity & entity)
{
}

void JoystickController::detach(bolt::Entity & entity)
{
}

void JoystickController::start(bolt::ControllerNode & node)
{
}

void JoystickController::handleJoystickMove(int devicenum, int joynum, float x, float y)
{
}

void JoystickController::handleJoystickButton(int devicenum, bolt::Button button, float state)
{
}
}
