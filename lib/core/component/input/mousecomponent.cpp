/*
 * mousecomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "mousecomponent.hpp"

namespace bolt
{
const std::string MouseComponent::KEY("mouse");

MouseComponent::MouseComponent()
: bolt::Component( KEY )
{
}

MouseComponent::~MouseComponent()
{
}

bool MouseComponent::initialize()
{
	return true;
}

void MouseComponent::getDependencies(bolt::StringSet & dep)
{
}

void MouseComponent::attach(bolt::Entity & entity)
{
}

void MouseComponent::detach(bolt::Entity & entity)
{
}

void MouseComponent::start(bolt::ComponentNode & node)
{
}

void MouseComponent::handleMouseMove(float x, float y)
{
}

void MouseComponent::handleMouseButton(bolt::Button button, float state)
{
}

void MouseComponent::handleMouseWheel(float val)
{
}
}

