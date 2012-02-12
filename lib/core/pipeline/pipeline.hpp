/*
 * pipeline.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef PIPELINE_HPP_
#define PIPELINE_HPP_

#include <common>
#include <exception>
#include <thread>
#include <tque>
#include "tools/controllernode.hpp"
#include <merge>
#include <entity.hpp>

namespace bolt
{
class Controller;
class Pipeline
{
private:
	static const uint CYCLE_NULL = 0;

	typedef std::set<Controller *> ControllerSet;
	typedef std::map<std::string,ControllerNode*> NodeNameMap;
	unsigned int cycle;

	Merge< std::mutex , ControllerSet > addSet;
	Merge< std::mutex , ControllerSet > removeSet;
	Merge< std::mutex , NodeNameMap > nameMap;

	// Internal tools for 'run'
	NodeSet roots;
	NodeSet nonConcurrent;
	NodeSet concurrent;
	TQue<ControllerNode*> waitingQue;

	void addToRoot( ControllerNode *node );
	void runAddSet();
	void runRemoveSet();
public:
	Pipeline();
	virtual ~Pipeline();

	void setCycle( uint val );
	uint getCycle();

	// Attach/Detach
	// These functions are volatile, the Pipeline does not transfer the ownership of the Controller* to Pipeline
	// but, if you detach, you must make sure that the Controller* lives, at least till the run cycle finishes.
	// IF you delete the controller before that.. No guarantees what happens.
	// probably the safest pattern is to a) detach controller b) kill the controller in the next cycle.
	void attach( Controller *controller ) throw (std::exception);
	void detach( Controller *controller ) throw (std::exception);

	void clear();

	void removeEntity( Entity& entity );

	// Run is the heart of the pipeline, it is essentially the main-loop.
	void run() throw (std::exception);
};

} /* namespace bolt */
#endif /* PIPELINE_HPP_ */

