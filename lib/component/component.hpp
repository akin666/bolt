/*
 * Component.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "entity.hpp"

namespace bolt
{

class ComponentWork;
class Component
{
protected:
	// SM_ID functionality
	static unsigned int sm_id;
	static unsigned int getNewId();

	unsigned int id;
	unsigned int priority;
	bool concurrent;
public:
	unsigned int getId() const;
	bool isConcurrent();
protected:
	// Concurrency functionality
	int concurrent_reference_counting;
public:
	unsigned int getPriority();
	void setPriority( unsigned int prio );

public:
	void addReference();
	void releaseReference();

	void schedule( ComponentWork& work );
	void finished( ComponentWork& work );
public:
	Component( bool concurrent = false);
	virtual ~Component();

	// Figure out if this component can be before the linked component
	virtual bool before( Component& component );

	// Attach / Detach an entity to the component.
	virtual void attach( Entity& entity ) = 0;
	virtual void detach( Entity& entity ) = 0;

	// Start can be blocking, if the component wants to go singlethreaded.
	// on multithreaded situation, it should start work on packages.
	virtual void start() = 0;
};

} /* namespace bolt */
#endif /* COMPONENT_HPP_ */
