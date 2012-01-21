/*
 * mousecomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef MOUSECOMPONENT_HPP_
#define MOUSECOMPONENT_HPP_

#include <component/component.hpp>
#include <common>

namespace bolt
{
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

	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( bolt::Button button , float state );
	virtual void handleMouseWheel( float val );
};
}

#endif /* MOUSECOMPONENT_HPP_ */
