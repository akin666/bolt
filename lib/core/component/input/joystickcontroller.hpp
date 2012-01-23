/*
 * JoystickController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef JOYSTICKCONTROLLER_HPP_
#define JOYSTICKCONTROLLER_HPP_

#include <component/controller.hpp>
#include <common>

namespace bolt
{
class JoystickController: public bolt::Controller
{
public:
	const static std::string KEY;
public:
	JoystickController();
	virtual ~JoystickController();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );

	virtual void handleJoystickMove( int devicenum , int joynum , float x , float y );
	virtual void handleJoystickButton( int devicenum , bolt::Button button , float state );
};
}

#endif /* JOYSTICKCONTROLLER_HPP_ */
