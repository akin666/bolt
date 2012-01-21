/*
 * joystickcomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef JOYSTICKCOMPONENT_HPP_
#define JOYSTICKCOMPONENT_HPP_

#include <component/component.hpp>
#include <common>

namespace bolt
{
class JoystickComponent: public bolt::Component
{
public:
	const static std::string KEY;
public:
	JoystickComponent();
	virtual ~JoystickComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );

	virtual void handleJoystickMove( int devicenum , int joynum , float x , float y );
	virtual void handleJoystickButton( int devicenum , bolt::Button button , float state );
};
}

#endif /* JOYSTICKCOMPONENT_HPP_ */
