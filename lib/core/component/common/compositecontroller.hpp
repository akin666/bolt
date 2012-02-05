/*
 * CompositeController.hpp
 *
 *  Created on: 6.2.2012
 *      Author: akin
 */

#ifndef COMPOSITECONTROLLER_HPP_
#define COMPOSITECONTROLLER_HPP_

#include <component/controller.hpp>
#include <common>
#include <vector>

namespace bolt
{

class CompositeController: public Controller
{
protected:
	typedef std::vector< Controller *> ControllerVector;
	ControllerVector controllers;
	bolt::StringSet& dependencies;
public:
	CompositeController( std::string cname , bolt::StringSet& dependencies );
	virtual ~CompositeController();

	void attach( Controller *other );
	void detach( Controller *other );

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( StringSet& dep );

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	virtual void clear();
	virtual void start( ControllerNode& node );
};

} /* namespace bolt */
#endif /* COMPOSITECONTROLLER_HPP_ */
