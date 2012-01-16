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
class ComponentNode
{
protected:
	Component& component;
	int concurrent_reference_counting;

	unsigned int time;
public:
	ComponentNode( Component& component );
	ComponentNode( ComponentNode& other );
	virtual ~ComponentNode();

	std::deque<ComponentNode *> dependencies;
	std::deque<ComponentNode *> childs;

	Component& getComponent();
	bool isRunning();

	void componentStart( TQue<ComponentNode*>& target , unsigned int start , unsigned int end );
	void componentFinished();

	// reference counting:
	void addReference();
	void releaseReference();

	// Component should use these to run stuff.
	void schedule( ComponentWork& work );
	void finished( ComponentWork& work );
};

} /* namespace bolt */
#endif /* COMPONENTNODE_HPP_ */
