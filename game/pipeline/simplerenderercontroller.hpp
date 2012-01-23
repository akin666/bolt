/*
 * SimpleRendererController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef SIMPLETENDERERCONTROLLER_HPP_
#define SIMPLETENDERERCONTROLLER_HPP_

#include <component/controller.hpp>

class SimpleRendererController: public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;
public:
	SimpleRendererController();
	virtual ~SimpleRendererController();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );
};

#endif /* SIMPLETENDERERCOMPONENT_HPP_ */