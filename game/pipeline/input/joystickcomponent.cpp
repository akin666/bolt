/*
 * joystickcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "joystickcomponent.hpp"

const std::string JoystickComponent::KEY("joystick");

JoystickComponent::JoystickComponent()
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



