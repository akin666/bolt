/*
 * CompositeController.cpp
 *
 *  Created on: 6.2.2012
 *      Author: akin
 */

#include "compositecontroller.hpp"

namespace bolt
{

CompositeController::CompositeController( std::string cname , bolt::StringSet& dependencies )
: Controller( cname ),
  dependencies( dependencies )
{
}

CompositeController::~CompositeController()
{
}

void CompositeController::attach(Controller *other)
{
	// Seek if it is already in:
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found controller already in the composition!.
		if( (*iter) == other )
		{
			return;
		}
	}

	controllers.push_back( other );
}

void CompositeController::detach(Controller *other)
{
	// Seek.
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		if( (*iter) == other )
		{
			controllers.erase( iter );
			return;
		}
	}
}

void CompositeController::initialize() throw (std::exception)
{
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		(*iter)->initialize();
	}
}

void CompositeController::getDependencies(StringSet & dep)
{
	dep = dependencies;

	StringSet set;
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		(*iter)->getDependencies( set );

		if( set.size() > 0 )
		{
			dep.insert( set.begin() , set.end() );
		}
	}
}

void CompositeController::attach(Entity & entity)
{
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		(*iter)->attach( entity );
	}
}

void CompositeController::detach(Entity & entity)
{
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		(*iter)->detach( entity );
	}
}

void CompositeController::clear()
{
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		(*iter)->clear();
	}
}

void CompositeController::start(ControllerNode & node)
{
	for( ControllerVector::iterator iter = controllers.begin() ; iter != controllers.end() ; ++iter )
	{
		// Found the controller in the composition!.
		(*iter)->start( node );
	}
}

} /* namespace bolt */


