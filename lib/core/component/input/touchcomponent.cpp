/*
 * touchcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "touchcomponent.hpp"

namespace bolt
{
const std::string TouchComponent::KEY("touch");

TouchComponent::TouchComponent()
: bolt::Component( KEY )
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

void TouchComponent::startTouch(int id, float x, float y)
{
}

void TouchComponent::continueTouch(int id, float x, float y)
{
}

void TouchComponent::endTouch(int id, float x, float y)
{
}
}