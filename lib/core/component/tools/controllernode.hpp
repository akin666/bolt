/*
 * controllernode.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef CONTROLLERNODE_HPP_
#define CONTROLLERNODE_HPP_

#include <common>
#include <set>
#include <tque>

namespace bolt
{

class Work;
class Controller;
class ComponentWork;

class ControllerNode;

typedef std::set<ControllerNode *> NodeSet;

class ControllerNode
{
protected:
	Controller& controller;
	int concurrent_reference_counting;

	uint cycle;

	NodeSet dependencies;
	NodeSet childs;

	// Where to push, once finished.
	TQue<ControllerNode*>& finishQueu;

	// reference counting:
	void addReference();
	void releaseReference();
public:
	ControllerNode( Controller& controller , TQue<ControllerNode*>& finishQueu );
	ControllerNode( ControllerNode& other );
	virtual ~ControllerNode();

	NodeSet& getDependencies();
	NodeSet& getChilds();

	Controller& get();
	uint getCycle();
	void setCycle( uint val );
	bool isRunning();

	void start( uint end );

	// Component should use these to run stuff.
	void schedule( ComponentWork& work );
	void finished( ComponentWork& work );

	void scheduleWork( Work& work );
};

} /* namespace bolt */
#endif /* COMPONENTNODE_HPP_ */
