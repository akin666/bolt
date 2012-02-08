/*
 * Mouse.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <common>

namespace bolt
{
class Mouse
{
public:
	Mouse();
	virtual ~Mouse();

	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( bolt::Button button , float state );
	virtual void handleMouseWheel( float val );
};
}

#endif /* MOUSE_HPP_ */
