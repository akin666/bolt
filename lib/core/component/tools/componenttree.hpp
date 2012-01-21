/*
 * componenttree.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef COMPONENTTREE_HPP_
#define COMPONENTTREE_HPP_

#include <deque>
#include <set>
#include <map>
#include <string>
#include <common>
#include "componentnode.hpp"

namespace bolt
{

class Component;

class ComponentTree
{
protected:
	NodeSet roots;
	std::map<std::string,ComponentNode*> nodeNameMap;

	void removeFromRoot( ComponentNode *node );
	void addToRoot( ComponentNode *node );
	TQue<ComponentNode*>& waitingQue;
public:
	ComponentTree( TQue<ComponentNode*>& waitingQue );
	virtual ~ComponentTree();

	void add( Component *component );
	void remove( Component *component );

	void resetCycle( uint val );
	void getRoots( NodeSet& roots );
};

} /* namespace bolt */
#endif /* COMPONENTTREE_HPP_ */
