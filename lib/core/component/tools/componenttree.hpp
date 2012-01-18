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

namespace bolt
{

class ComponentNode;
class Component;
typedef std::deque<ComponentNode*> TreeNodeSet;
class ComponentTree
{
protected:
	TreeNodeSet roots;
	TreeNodeSet nodes;
	std::map<std::string,ComponentNode*> nodeNameMap;

	void removeFromRoot( ComponentNode *node );
	void addToRoot( ComponentNode *node );
public:
	ComponentTree();
	virtual ~ComponentTree();

	void add( Component *component );

	void resetCycle( uint val );
	void getRoots( TreeNodeSet& roots );
};

} /* namespace bolt */
#endif /* COMPONENTTREE_HPP_ */
