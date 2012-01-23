/*
 * prototype.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef PROTOTYPE_HPP_
#define PROTOTYPE_HPP_

#include <set>
#include "entity.hpp"
#include "controller.hpp"

namespace bolt
{

typedef std::set<Controller*> ControllerSet;

class Prototype
{
protected:
	ControllerSet controllers;
public:
	Prototype();
	virtual ~Prototype();

	void add( Controller& controller );

	void attach( Entity& entity );
	Entity create();
};

} /* namespace bolt */
#endif /* PROTOTYPE_HPP_ */
