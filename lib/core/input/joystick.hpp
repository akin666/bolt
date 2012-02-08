/*
 * JOYSTICK_HPP_.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef JOYSTICK_HPP_
#define JOYSTICK_HPP_

#include <common>

namespace bolt
{
class Joystick
{
public:
	Joystick();
	virtual ~Joystick();

	virtual void handleJoystickMove( int devicenum , int joynum , float x , float y );
	virtual void handleJoystickButton( int devicenum , bolt::Button button , float state );
};
}

#endif /* JOYSTICK_HPP_ */
