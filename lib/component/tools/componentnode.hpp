/*
 * componentnode.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENTNODE_HPP_
#define COMPONENTNODE_HPP_

namespace bolt
{

class Component;
class ComponentWork;
class ComponentNode
{
protected:
	Component& component;
	int concurrent_reference_counting;

	unsigned int time;

	std::deque<ComponentNode *> dependencies;
	std::deque<ComponentNode *> childs;

	// reference counting:
	void addReference();
	void releaseReference();
public:
	ComponentNode( Component& component );
	ComponentNode( ComponentNode& other );
	virtual ~ComponentNode();

	std::deque<ComponentNode *>& getDependencies();
	std::deque<ComponentNode *>& getChilds();

	Component& getComponent();
	unsigned int getTime();
	bool isRunning();

	void start( unsigned int start , unsigned int end );

	// Component should use these to run stuff.
	void schedule( ComponentWork& work );
	void finished( ComponentWork& work );
};

} /* namespace bolt */
#endif /* COMPONENTNODE_HPP_ */
