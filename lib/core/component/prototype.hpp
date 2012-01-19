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
#include "component.hpp"

namespace bolt
{

typedef std::set<Component*> ComponentSet;

class Component;
class Prototype
{
protected:
	ComponentSet components;
public:
	Prototype();
	virtual ~Prototype();

	void add( Component& component );

	void attach( Entity& entity );
	Entity create();
};

} /* namespace bolt */
#endif /* PROTOTYPE_HPP_ */
