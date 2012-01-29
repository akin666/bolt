/*
 * controller.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <exception>
#include "entity.hpp"
#include <set>
#include <string>

namespace bolt
{

typedef std::set<std::string> StringSet;

class ComponentWork;
class ControllerNode;
class Controller
{
protected:
	// SM_ID functionality
	static uint sm_id;
	static uint getNewId();

	uint id;
	uint priority;
	std::string name;
	bool concurrent;
public:
	uint getId() const;
	bool isConcurrent() const;
	std::string getName() const;

	uint getPriority() const;
	void setPriority( uint prio );
public:
	/////
	// Following functions create the interface.
	/////
	Controller( std::string name , bool concurrent = false);
	virtual ~Controller();

	// Create or initialize also the components Property'es
	virtual void initialize() throw (std::exception);

	// Figure out what controllers should be before this controller.
	virtual void getDependencies( StringSet& dep );

	// Attach / Detach an entity to the component.
	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	// Start can be blocking, if the controller wants to do singlethreaded.
	// on multithreaded situation, it should start work on packages.
	// Use ComponentNode to start all sort of crazy work tasks etc.
	virtual void start( ControllerNode& node ) = 0;
};

} /* namespace bolt */
#endif /* CONTROLLER_HPP_ */
