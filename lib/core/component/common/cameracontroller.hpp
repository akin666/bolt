/*
 * cameracontroller.hpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#ifndef CAMERACONTROLLER_HPP_
#define CAMERACONTROLLER_HPP_

#include <component/controller.hpp>
#include <common>

namespace bolt
{

class CameraController: public bolt::Controller
{
public:
	const static std::string KEY;
public:
	CameraController();
	virtual ~CameraController();

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( StringSet& dep );

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	virtual void clear();
	virtual void start( ControllerNode& node ) throw (std::exception);
};

} /* namespace bolt */
#endif /* CAMERACONTROLLER_HPP_ */
