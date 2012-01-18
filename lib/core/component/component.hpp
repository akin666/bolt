/*
 * Component.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "entity.hpp"
#include <set>
#include <string>

namespace bolt
{

typedef std::set<std::string> StringSet;

class ComponentWork;
class ComponentNode;
class Component
{
protected:
	// SM_ID functionality
	static unsigned int sm_id;
	static unsigned int getNewId();

	unsigned int id;
	unsigned int priority;
	std::string name;
	bool concurrent;
public:
	unsigned int getId() const;
	bool isConcurrent() const;
	std::string getName() const;

	unsigned int getPriority() const;
	void setPriority( unsigned int prio );
public:
	/////
	// Following functions create the interface.
	/////
	Component( std::string name = "" , bool concurrent = false);
	virtual ~Component();

	virtual bool initialize();

	// Figure out what components should be before this component.
	virtual void getDependencies( StringSet& dep );

	// Attach / Detach an entity to the component.
	virtual void attach( Entity& entity ) = 0;
	virtual void detach( Entity& entity ) = 0;

	// Start can be blocking, if the component wants to do singlethreaded.
	// on multithreaded situation, it should start work on packages.
	// Use ComponentNode to start all sort of crazy work tasks etc.
	virtual void start( ComponentNode& node ) = 0;
};

} /* namespace bolt */
#endif /* COMPONENT_HPP_ */
