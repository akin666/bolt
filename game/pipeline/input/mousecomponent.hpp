/*
 * mousecomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef MOUSECOMPONENT_HPP_
#define MOUSECOMPONENT_HPP_

#include <component/component.hpp>

class MouseComponent: public bolt::Component
{
public:
	const static std::string KEY;
public:
	MouseComponent();
	virtual ~MouseComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );
};

#endif /* MOUSECOMPONENT_HPP_ */
