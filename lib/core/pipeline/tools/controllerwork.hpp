/*
 * ControllerWork.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef CONTROLLERWORK_HPP_
#define CONTROLLERWORK_HPP_

#include <work>

namespace bolt
{
class ControllerNode;

class ControllerWork : public Work
{
protected:
	ControllerNode *parent;
public:
	void set( ControllerNode *co );
public:
	ControllerWork();
	virtual ~ControllerWork();

	// Inheriting classes are responsible to produce exact same
	// action as begin and end are doing in this class.
	virtual bool begin();
	virtual void run() = 0;
	virtual void end();
};

} /* namespace bolt */
#endif /* CONTROLLERWORK_HPP_ */
