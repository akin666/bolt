/*
 * keyboardinputhandler.hpp
 *
 *  Created on: 10.1.2012
 *      Author: akin
 */

#ifndef KEYBOARDINPUTHANDLER_HPP_
#define KEYBOARDINPUTHANDLER_HPP_

#include <common>

namespace bolt
{

class KeyboardInputHandler
{
public:
	KeyboardInputHandler();
	virtual ~KeyboardInputHandler();

	virtual void handleKeyboard( unsigned int key , float state );
	virtual void handleKeyboardCharacter( unsigned int key , float state );
};

} /* namespace bolt */
#endif /* KEYBOARDINPUTHANDLER_HPP_ */
