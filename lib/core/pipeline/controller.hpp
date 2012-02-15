/*
 * controller.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 *
 *      Controller is like the controller from the ModelViewController pattern.
 *      Controller adds some functionality to the entities.. and is designed to control the Property classes.
 *      The design of controller is coupled deeply, with the Pipeline concept, and actually, pipeline, is just
 *      a set of parallel and nonparallel controllers, that do some single task well..
 *
 *      The original idea, is to use the pipeline to control safe/nonsafe threading, so that, for example, PhysicsController
 *      can modify PositionProperty data, while ScriptController can do something else, and not touch the PositionProperty data.
 */

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <set>
#include <string>
#include <common>
#include <entity.hpp>

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
	virtual void initialize();

	// Figure out what controllers should be before this controller.
	virtual void getDependencies( StringSet& dep );

	// Attach / Detach an entity to the component.
	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	// detach all entities & clear the whole blody component.
	// this gets called when attaching to pipeline.
	virtual void clear();

	// Start can be blocking, if the controller wants to do singlethreaded.
	// on multithreaded situation, it should start work on packages.
	// Use ComponentNode to start all sort of crazy work tasks etc.
	virtual void start( ControllerNode& node ) = 0;
};

} /* namespace bolt */
#endif /* CONTROLLER_HPP_ */
