/*
 * simpletenderercomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef SIMPLETENDERERCOMPONENT_HPP_
#define SIMPLETENDERERCOMPONENT_HPP_

#include <component/component.hpp>

class SimpleRendererComponent: public bolt::Component
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;
public:
	SimpleRendererComponent();
	virtual ~SimpleRendererComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );
};

#endif /* SIMPLETENDERERCOMPONENT_HPP_ */
