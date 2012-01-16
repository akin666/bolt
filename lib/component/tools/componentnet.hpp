/*
 * componentnet.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENTNET_HPP_
#define COMPONENTNET_HPP_

#include <deque>
#include <set>
#include "componentnode.hpp"

namespace bolt
{

class ComponentNet
{
public:
	unsigned int time;
protected:
	std::deque<ComponentNode*> roots;
	std::deque<ComponentNode> nodes;
	std::set<Component&> components;

	void removeFromRoot( ComponentNode *node );
	void addToRoot( ComponentNode *node );
public:
	ComponentNet();
	virtual ~ComponentNet();

	void add( Component& component );

	void resetTime( Time time );

	void getRoot( std::deque<ComponentNode*>& root );
};

} /* namespace bolt */
#endif /* COMPONENTNET_HPP_ */
