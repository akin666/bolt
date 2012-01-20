/*
 * keyboardcomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef KEYBOARDCOMPONENT_HPP_
#define KEYBOARDCOMPONENT_HPP_

#include <component/component.hpp>

class KeyboardComponent: public bolt::Component
{
public:
	const static std::string KEY;
public:
	KeyboardComponent();
	virtual ~KeyboardComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );
};

#endif /* KEYBOARDCOMPONENT_HPP_ */
