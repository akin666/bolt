/*
 * componentnode.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENTNODE_HPP_
#define COMPONENTNODE_HPP_

#include <common>
#include <set>
#include <tque>

namespace bolt
{

class Work;
class Component;
class ComponentWork;

class ComponentNode;

typedef std::set<ComponentNode *> NodeSet;

class ComponentNode
{
protected:
	Component& component;
	int concurrent_reference_counting;

	uint cycle;

	NodeSet dependencies;
	NodeSet childs;

	// Where to push, once finished.
	TQue<ComponentNode*>& finishQueu;

	// reference counting:
	void addReference();
	void releaseReference();
public:
	ComponentNode( Component& component , TQue<ComponentNode*>& finishQueu );
	ComponentNode( ComponentNode& other );
	virtual ~ComponentNode();

	NodeSet& getDependencies();
	NodeSet& getChilds();

	Component& getComponent();
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
