/*
 * MouseController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef MOUSECONTROLLER_HPP_
#define MOUSECONTROLLER_HPP_

#include <component/controller.hpp>
#include <common>

namespace bolt
{
class MouseController: public bolt::Controller
{
public:
	const static std::string KEY;
public:
	MouseController();
	virtual ~MouseController();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );

	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( bolt::Button button , float state );
	virtual void handleMouseWheel( float val );
};
}

#endif /* MOUSECONTROLLER_HPP_ */
