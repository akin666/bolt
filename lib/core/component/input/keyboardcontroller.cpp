/*
 * keyboardcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "keyboardcontroller.hpp"

namespace bolt
{
const std::string KeyboardController::KEY("keyboard");

KeyboardController::KeyboardController()
: bolt::Controller( KEY )
{
}

KeyboardController::~KeyboardController()
{
}

bool KeyboardController::initialize()
{
	return true;
}

void KeyboardController::getDependencies(bolt::StringSet & dep)
{
}

void KeyboardController::attach(bolt::Entity & entity)
{
}

void KeyboardController::detach(bolt::Entity & entity)
{
}

void KeyboardController::start(bolt::ControllerNode & node)
{
}

void KeyboardController::handleKeyboard(unsigned int key, float state)
{
}

void KeyboardController::handleKeyboardCharacter(unsigned int key, float state)
{
}
}
