/*
 * mousecomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "mousecomponent.hpp"

const std::string MouseComponent::KEY("mouse");

MouseComponent::MouseComponent()
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

void NameComponent::detach(bolt::Entity & entity)
{
}

void NameComponent::start(bolt::ComponentNode & node)
{
}

