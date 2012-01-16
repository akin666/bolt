/*
 * componentwork.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENTWORK_HPP_
#define COMPONENTWORK_HPP_

#include <work>

namespace bolt
{
class Component;

class ComponentWork : public Work
{
protected:
	Component *parent;
public:
	void setComponent( Component *component );
public:
	ComponentWork();
	virtual ~ComponentWork();

	// Inheriting classes are responsible to produce exact same
	// action as begin and end are doing in this class.
	virtual bool begin();
	virtual void run() = 0;
	virtual void end();
};

} /* namespace bolt */
#endif /* COMPONENTWORK_HPP_ */
