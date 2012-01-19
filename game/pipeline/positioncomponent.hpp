/*
 * positioncomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include <component/component.hpp>

class PositionComponent: public bolt::Component
{
public:
	const static std::string KEY;
public:
	PositionComponent();
	virtual ~PositionComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );
};

#endif /* POSITIONCOMPONENT_HPP_ */
