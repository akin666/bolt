/*
 * componenttree.cpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#include "componenttree.hpp"
#include <component/component.hpp>
#include "componentnode.hpp"
#include <iostream>

namespace bolt
{

ComponentTree::ComponentTree()
{
}

ComponentTree::~ComponentTree()
{
}

void ComponentTree::removeFromRoot( ComponentNode *node )
{
	for( std::deque<ComponentNode*>::iterator iter = roots.begin() ; iter != roots.end() ; ++iter )
	{
		if( *iter == node )
		{
			roots.erase( iter );
			return;
		}
	}
}

void ComponentTree::addToRoot( ComponentNode *node )
{
	if( node->dependencies.size() == 0 )
	{
		// no parent.
		roots.push_back( node );
	}
}

void ComponentTree::resetTime( Time time )
{
	for( std::deque<ComponentNode*>::iterator iter = nodes.begin() ; iter != nodes.end() ; ++iter )
	{
		(*iter)->time = time;
	}
}

void ComponentTree::add( Component *component )
{
	if( component == NULL )
	{
		return;
	}

	// already has it
	if( componentNameMap.find( component->getName() ) != componentNameMap.end() )
	{
		return;
	}

	ComponentNode *node = new ComponentNode( *component );

	StringSet dependencies;
	component->getDependencies( dependencies );

	// Seek Parent dependencies.
	// If found, link em.
	std::map<std::string , ComponentNode*>::iterator citer;
	for( StringSet::iterator iter = dependencies.begin() ; iter != dependencies.end() ; ++iter )
	{
		citer = componentNameMap.find( *iter );

		if( citer != componentNameMap.end() )
		{
			// found!
			ComponentNode *dependencyNode = citer->second;

			node->getDependencies().push_back( dependencyNode );
			dependencyNode->getChilds().push_back( node );
		}
	}

	// Seek child dependencies.
	// If found, link em.
	std::string name = component->getName();
	for( std::deque<ComponentNode*>::iterator iter = nodes.begin() ; iter != nodes.end() ; ++iter )
	{
		ComponentNode *dependencyNode = *iter;

		// Reuse list..
		dependencyNode->getComponent().getDependencies( dependencies );

		// No dependency?
		if( dependencies.find( name ) == dependencies.end() )
		{
			continue;
		}

		// Dependency, link em.
		dependencyNode->getDependencies().push_back( node );
		node->getChilds().push_back( dependencyNode );

		if( dependencyNode->getDependencies().size() == 1 )
		{
			// First parent! Remove from root!
			removeFromRoot( dependencyNode );
		}
	}

	nodes.push_back( node );

	// try to add as root element..
	addToRoot( node );

	resetTime( 0 );
}

void ComponentTree::getRoots( std::deque<ComponentNode*>& root )
{
	root = roots;
}

} /* namespace bolt */
