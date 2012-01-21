/*
 * keyboardcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "keyboardcomponent.hpp"

namespace bolt
{
const std::string KeyboardComponent::KEY("keyboard");

KeyboardComponent::KeyboardComponent()
: bolt::Component( KEY )
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

void KeyboardComponent::handleKeyboard(unsigned int key, float state)
{
}

void KeyboardComponent::handleKeyboardCharacter(unsigned int key, float state)
{
}
}
