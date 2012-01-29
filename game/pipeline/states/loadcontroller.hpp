/*
 * loadcontroller.hpp
 *
 *  Created on: 29.1.2012
 *      Author: akin
 */

#ifndef LOADCONTROLLER_HPP_
#define LOADCONTROLLER_HPP_

#include <component/controller.hpp>

class LoadController: public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;

	bool loadComplete;
public:
	LoadController();
	virtual ~LoadController();

	virtual void initialize() throw (std::exception);
	virtual void start( bolt::ControllerNode& node );
};

#endif /* LOADCONTROLLER_HPP_ */
