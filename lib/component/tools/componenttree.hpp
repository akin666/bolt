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
#include "componentnode.hpp"
#include <map>

namespace bolt
{

typedef std::deque<ComponentNode*> TreeNodeSet;
class ComponentTree
{
public:
	unsigned int time;
protected:
	TreeNodeSet roots;
	TreeNodeSet nodes;
	std::map<std::string,Component*> componentNameMap;

	void removeFromRoot( ComponentNode *node );
	void addToRoot( ComponentNode *node );
public:
	ComponentTree();
	virtual ~ComponentTree();

	void add( Component *component );

	void resetTime( Time time );

	void getRoots( TreeNodeSet& roots );
};

} /* namespace bolt */
#endif /* COMPONENTTREE_HPP_ */
