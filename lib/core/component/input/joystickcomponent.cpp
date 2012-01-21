/*
 * joystickcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "joystickcomponent.hpp"

namespace bolt
{
const std::string JoystickComponent::KEY("joystick");

JoystickComponent::JoystickComponent()
: bolt::Component( KEY )
{
}

JoystickComponent::~JoystickComponent()
{
}

bool JoystickComponent::initialize()
{
	return true;
}

void JoystickComponent::getDependencies(bolt::StringSet & dep)
{
}

void JoystickComponent::attach(bolt::Entity & entity)
{
}

void JoystickComponent::detach(bolt::Entity & entity)
{
}

void JoystickComponent::start(bolt::ComponentNode & node)
{
}

void JoystickComponent::handleJoystickMove(int devicenum, int joynum, float x, float y)
{
}

void JoystickComponent::handleJoystickButton(int devicenum, bolt::Button button, float state)
{
}
}
