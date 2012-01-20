/*
 * touchcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "touchcomponent.hpp"

const std::string TouchComponent::KEY("touch");

TouchComponent::TouchComponent()
{
}

TouchComponent::~TouchComponent()
{
}

bool TouchComponent::initialize()
{
	return true;
}

void TouchComponent::getDependencies(bolt::StringSet & dep)
{
}

void TouchComponent::attach(bolt::Entity & entity)
{
}

void TouchComponent::detach(bolt::Entity & entity)
{
}

void TouchComponent::start(bolt::ComponentNode & node)
{
}


