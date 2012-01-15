/*
 * joystickinputhandler.hpp
 *
 *  Created on: 10.1.2012
 *      Author: akin
 */

#ifndef JOYSTICKINPUTHANDLER_HPP_
#define JOYSTICKINPUTHANDLER_HPP_

#include <common>

namespace bolt
{

class JoystickInputHandler
{
public:
	JoystickInputHandler();
	virtual ~JoystickInputHandler();

	virtual void handleJoystickMove( int devicenum , int joynum , float x , float y );
	virtual void handleJoystickButton( int devicenum , Button button , float state );
};

} /* namespace bolt */
#endif /* JOYSTICKINPUTHANDLER_HPP_ */
