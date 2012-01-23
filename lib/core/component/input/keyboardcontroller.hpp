/*
 * KeyboardController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef KEYBOARDCONTROLLER_HPP_
#define KEYBOARDCONTROLLER_HPP_

#include <component/controller.hpp>

namespace bolt
{
class KeyboardController: public bolt::Controller
{
public:
	const static std::string KEY;
public:
	KeyboardController();
	virtual ~KeyboardController();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );

	virtual void handleKeyboard( unsigned int key , float state );
	virtual void handleKeyboardCharacter( unsigned int key , float state );
};
}

#endif /* KEYBOARDCONTROLLER_HPP_ */
