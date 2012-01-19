/*
 * namecomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef NAMECOMPONENT_HPP_
#define NAMECOMPONENT_HPP_

#include <component/component.hpp>

class NameComponent: public bolt::Component
{
public:
	const static std::string KEY;
public:
	NameComponent();
	virtual ~NameComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );
};

#endif /* NAMECOMPONENT_HPP_ */
