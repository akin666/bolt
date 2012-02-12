/*
 * inputcontroller.hpp
 *
 *  Created on: 9.2.2012
 *      Author: akin
 */

#ifndef INPUTCONTROLLER_HPP_
#define INPUTCONTROLLER_HPP_

#include <input/keyboard.hpp>
#include <input/mouse.hpp>
#include <pipeline/controller.hpp>

class InputController : public bolt::Keyboard , public bolt::Mouse , public bolt::Controller
{
public:
	InputController();
	virtual ~InputController();

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );

	// Keyboard
	virtual void handleKeyboard( unsigned int key , float state );
	virtual void handleKeyboardCharacter( unsigned int key , float state );

	// Mouse
	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( bolt::Button button , float state );
	virtual void handleMouseWheel( float val );
};

#endif /* INPUTCONTROLLER_HPP_ */
