/*
 * TouchController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef TOUCHCONTROLLER_HPP_
#define TOUCHCONTROLLER_HPP_

#include <component/controller.hpp>

namespace bolt
{
class TouchController: public bolt::Controller
{
public:
	const static std::string KEY;
public:
	TouchController();
	virtual ~TouchController();

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );

	virtual void startTouch( int id , float x , float y );
	virtual void continueTouch( int id , float x , float y );
	virtual void endTouch( int id , float x , float y );
};
}

#endif /* TOUCHCONTROLLER_HPP_ */
