/*
 * keyboardcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "keyboardcomponent.hpp"

const std::string KeyboardComponent::KEY("keyboard");

KeyboardComponent::KeyboardComponent()
{
}

KeyboardComponent::~KeyboardComponent()
{
}

bool KeyboardComponent::initialize()
{
	return true;
}

void KeyboardComponent::getDependencies(bolt::StringSet & dep)
{
}

void KeyboardComponent::attach(bolt::Entity & entity)
{
}

void KeyboardComponent::detach(bolt::Entity & entity)
{
}

void KeyboardComponent::start(bolt::ComponentNode & node)
{
}



