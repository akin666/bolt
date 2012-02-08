/*
 * joystickcomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "joystick.hpp"

namespace bolt
{

Joystick::Joystick()
{
}

Joystick::~Joystick()
{
}

void Joystick::handleJoystickMove(int devicenum, int joynum, float x, float y)
{
}

void Joystick::handleJoystickButton(int devicenum, bolt::Button button, float state)
{
}

}
