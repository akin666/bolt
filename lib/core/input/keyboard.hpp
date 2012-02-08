/*
 * KeyboardController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <common>

namespace bolt
{
class Keyboard
{
public:
	Keyboard();
	virtual ~Keyboard();

	virtual void handleKeyboard( unsigned int key , float state );
	virtual void handleKeyboardCharacter( unsigned int key , float state );
};
}

#endif /* KEYBOARD_HPP_ */
