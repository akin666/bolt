/*
 * Touch.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef TOUCH_HPP_
#define TOUCH_HPP_

#include <component/controller.hpp>

namespace bolt
{
class Touch
{
public:
	Touch();
	virtual ~Touch();

	virtual void startTouch( int id , float x , float y );
	virtual void continueTouch( int id , float x , float y );
	virtual void endTouch( int id , float x , float y );
};
}

#endif /* TOUCH_HPP_ */
