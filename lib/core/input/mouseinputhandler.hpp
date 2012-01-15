/*
 * mouseinputhandler.hpp
 *
 *  Created on: 10.1.2012
 *      Author: akin
 */

#ifndef MOUSEINPUTHANDLER_HPP_
#define MOUSEINPUTHANDLER_HPP_

#include <common>

namespace bolt
{

class MouseInputHandler
{
public:
	MouseInputHandler();
	virtual ~MouseInputHandler();

	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( Button button , float state );
	virtual void handleMouseButtonAction( Button );
	virtual void handleMouseWheel( float val );
};

} /* namespace bolt */
#endif /* MOUSEINPUTHANDLER_HPP_ */
