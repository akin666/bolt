/*
 * accelerometer.hpp
 *
 *  Created on: 17.2.2012
 *      Author: akin
 */

#ifndef ACCELEROMETER_HPP_
#define ACCELEROMETER_HPP_

namespace bolt
{

class Accelerometer
{
public:
	Accelerometer();
	virtual ~Accelerometer();

	virtual void handleAcceleroMove( float x , float y , float z );
};

} /* namespace bolt */
#endif /* ACCELEROMETER_HPP_ */
