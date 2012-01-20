/*
 * touchcomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef TOUCHCOMPONENT_HPP_
#define TOUCHCOMPONENT_HPP_

#include <component/component.hpp>

class TouchComponent: public bolt::Component
{
public:
	const static std::string KEY;
public:
	TouchComponent();
	virtual ~TouchComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );

	virtual void startTouch( int id , float x , float y );
	virtual void continueTouch( int id , float x , float y );
	virtual void endTouch( int id , float x , float y );
};

#endif /* TOUCHCOMPONENT_HPP_ */
