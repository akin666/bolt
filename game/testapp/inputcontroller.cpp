/*
 * inputcontroller.cpp
 *
 *  Created on: 9.2.2012
 *      Author: akin
 */

#include "inputcontroller.hpp"
#include <log>

InputController::InputController()
: bolt::Controller("inputcontroller" , false )
{
}

InputController::~InputController()
{
}

void InputController::initialize() throw (std::exception)
{
	LOG_OUT << "Input init" << std::endl;
}

void InputController::getDependencies(bolt::StringSet & dep)
{
}

void InputController::attach(bolt::Entity & entity)
{
}

void InputController::detach(bolt::Entity & entity)
{
}

void InputController::start(bolt::ControllerNode & node)
{
	// deliver input actions.. ?
}

void InputController::handleKeyboard(unsigned int key, float state)
{
	LOG_OUT << "Input handleKeyboard " << key << " state " << state << std::endl;
}

void InputController::handleKeyboardCharacter(unsigned int key, float state)
{
	LOG_OUT << "Input handleKeyboardCharacter " << key << " state " << state << std::endl;
}

void InputController::handleMouseMove(float x, float y)
{
	LOG_OUT << "Input handleMouseMove x:" << x << " y:" << y << std::endl;
}

void InputController::handleMouseButton(bolt::Button button, float state)
{
	LOG_OUT << "Input handleMouseButton " << button << " state " << state << std::endl;
}

void InputController::handleMouseWheel(float val)
{
	LOG_OUT << "Input handleMouseWheel " << val << std::endl;
}


