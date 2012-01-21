/*
 * componenttree.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "componenttree.hpp"
#include "componentnode.hpp"
#include <iostream>
#include <component/component.hpp>

namespace bolt
{

ComponentTree::ComponentTree( TQue<ComponentNode*>& waitingQue )
: waitingQue( waitingQue )
{
}

ComponentTree::~ComponentTree()
{
}

void ComponentTree::removeFromRoot( ComponentNode *node )
{
	roots.erase( node );
}

void ComponentTree::addToRoot( ComponentNode *node )
{
	if( node != NULL && node->getDependencies().size() == 0 )
	{
		// no parent.
		roots.insert( node );
	}
}

void ComponentTree::resetCycle( uint val )
{
	for( std::map<std::string , ComponentNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
	{
		iter->second->setCycle( val );
	}
}

void ComponentTree::add( Component *component )
{
	if( component == NULL )
	{
		return;
	}

	// already has it
	if( nodeNameMap.find( component->getName() ) != nodeNameMap.end() )
	{
		return;
	}

	ComponentNode *node = new ComponentNode( *component , waitingQue );

	StringSet dependencies;
	component->getDependencies( dependencies );

	// Seek Parent dependencies.
	// If found, link em.
	std::map<std::string , ComponentNode*>::iterator citer;
	for( StringSet::iterator iter = dependencies.begin() ; iter != dependencies.end() ; ++iter )
	{
		citer = nodeNameMap.find( *iter );

		if( citer != nodeNameMap.end() )
		{
			// found!
			ComponentNode *dependencyNode = citer->second;

			node->getDependencies().insert( dependencyNode );
			dependencyNode->getChilds().insert( node );
		}
	}

	// Seek child dependencies.
	// If found, link em.
	std::string name = component->getName();
	for( std::map<std::string , ComponentNode*>::iterator iter = nodeNameMap.begin() ; iter != nodeNameMap.end() ; ++iter )
	{
		ComponentNode *dependencyNode = iter->second;

		// Reuse list..
		dependencyNode->getComponent().getDependencies( dependencies );

		// No dependency?
		if( dependencies.find( name ) == dependencies.end() )
		{
			continue;
		}

		// Dependency, link em.
		dependencyNode->getDependencies().insert( node );
		node->getChilds().insert( dependencyNode );

		if( dependencyNode->getDependencies().size() == 1 )
		{
			// First parent! Remove from root!
			removeFromRoot( dependencyNode );
		}
	}

	// try to add as root element..
	addToRoot( node );

	resetCycle( 0 );
}

void ComponentTree::remove( Component *component )
{
	if( component == NULL )
	{
		return;
	}

	std::map<std::string , ComponentNode*>::iterator iter = nodeNameMap.find( component->getName() );

	// does not have it..
	if( iter == nodeNameMap.end() )
	{
		return;
	}

	ComponentNode *node = iter->second;

	// remove from namemap.
	nodeNameMap.erase( iter );

	if( node == NULL )
	{
		return;
	}

	// remove node from the lists.
	if( roots.find( node ) != roots.end() )
	{
		roots.erase( node );
	}

	// remove parent from childs
	// and link new child parent relation
	// or add to roots.
	bool root = node->getDependencies().size() > 0;
	for( NodeSet::iterator iter = node->getChilds().begin() ; iter != node->getChilds().end() ; ++iter )
	{
		(*iter)->getDependencies().erase( node );

		for( NodeSet::iterator piter = node->getDependencies().begin() ; piter != node->getDependencies().end() ; ++piter )
		{
			(*iter)->getDependencies().insert( *piter );
			(*piter)->getChilds().insert( *iter );
		}

		if( !root )
		{
			addToRoot( *iter );
		}
	}
}

void ComponentTree::getRoots( NodeSet& root )
{
	root = roots;
}

} /* namespace bolt */
